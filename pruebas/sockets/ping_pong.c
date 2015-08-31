/*
   Ejemplo de un ping pong simple con UDP.
   Este ejemplo TIENE UN BUG hecho con fines didacticos.

   La idea de un ping pong es la siguiente:
      1) Se ejecuta el proceso 'pong' que espera a recibir el mensaje ping:
          ./ping_pong pong
      2) En otra consola se lanza el proceso 'ping' que emitira el mensaje ping:
          ./ping_pong ping
      3) El proceso pong leera el mensaje y respondera, naturalmente, con un mensaje
         pong. Luego, ambos proceso terminan.

   Se compila con 
      gcc -std=c99 -o ping_pong ping_pong.c 

   Se ejecuta como
      ./ping_pong TYPE

   donde TYPE puede ser 'ping' o 'pong'.

   Este es un ejemplo MUY simple... y aun asi tiene un bug terrible, denle
   una mirada a ver si lo encuentran.
*/

/*
   Este define le dice a nuestro compilador que queremos 
   usar las extensiones POSIX.

   getaddrinfo, gai_error y freeaddrinfo no estan incluidas en el
   estandar C99 pero si en las ultimas versiones de POSIX.
   
   Con esto le decimos al compilador que esta OK
*/
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 1
#endif

/*
   Includes clasicos de C
*/
#include <string.h>
#include <stdio.h>
#include <errno.h>

#include <stdbool.h>

/*
   Includes mas propios de la familia *nix.
   Funciones como socket, connect, close son propias del
   sistema operativo.
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#define BUF_SIZE 256

void print_buf(char buf[]) {
   buf[4] = 0;            // prevenimos un overflow :)
   //printf("%s\n", buf);
   printf(buf);
   printf("\n");
}


int create_socket(const char* port_number) {
   struct addrinfo hints;
   struct addrinfo *ptr;

   int skt, s;

   bool socket_fail = false;

   memset(&hints, 0, sizeof(struct addrinfo));
   hints.ai_family = AF_INET;       /* IPv4 (or AF_INET6 for IPv6)     */
   hints.ai_socktype = SOCK_DGRAM;  /* UDP */
   hints.ai_flags = AI_NUMERICSERV; /* El 'servicio' sera un puerto numerico 'hardcodeado' */

   /* Buscamos una direccion valida para la maquina local, con puerto 2021/2022 */
   s = getaddrinfo(NULL, port_number, &hints, &ptr);

   if (s != 0) { 
      printf("Error in getaddrinfo: %s\n", gai_strerror(s));
      return -1;
   }

   /* Creamos el socket para internet (IPv4) de tipo UDP */
   skt = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

   if (skt == -1) {
      printf("Error: %s\n", strerror(errno));
      socket_fail = true;
   }

   if (!socket_fail) {
     s = bind(skt, ptr->ai_addr, ptr->ai_addrlen);
     if (s == -1) {
        printf("Error: %s\n", strerror(errno));
        close(skt);
        socket_fail = true;
     }
   }

   // Liberamos los recursos
   freeaddrinfo(ptr);
   
   if (socket_fail) {
     return -1;
   }

   return skt;
}


int main(int argc, char *argv[]) {
   struct addrinfo addr;
   struct addrinfo hints;
   struct addrinfo *ptr;

   int skt, s;
   bool are_we_a_pong;

   const char *ping_port = "2021";
   const char *pong_port = "2022";

   bool socket_fail = false;
   char buf[BUF_SIZE] = "P NG!!";

   if (argc != 2) {
      printf("Bad params.\nUsage ./ping-pong 'ping'   to send ping message\n      ./ping-pong 'pong'   to wait for a ping message and send a pong message.");
      return 1;
   }

   if (strncmp(argv[1], "ping", 5) == 0) {
      are_we_a_pong = false;
      buf[1] = 'I';
   }
   else if (strncmp(argv[1], "pong", 5) == 0) {
      are_we_a_pong = true;
      buf[1] = 'O';
   }
   else {
      printf("Bad params.\nUsage ./ping-pong 'ping'   to send ping message\n      ./ping-pong 'pong'   to wait for a ping message and send a pong message.");
      return 1;
   }

   // Creamos nuestro socket con una funcion auxiliar. Si algo falla, la funcion
   // se encargara de liberar todos los recursos y retornarnos un -1.
   // Si la funcion termina con exito, el valor de retorno sera un socket
   // el cual deberemos liberar con un close nosotros.
   skt = create_socket(are_we_a_pong? pong_port : ping_port);

   if (skt == -1) {
     return -1;
   }
      
   /* Definimos la direccion destino: con UDP podemos enviarle mensajes
    * a varios destinatarios con el mismo socket. No existe el concepto
    * de coneccion 1-a-1.
    * */
   memset(&hints, 0, sizeof(struct addrinfo));
   hints.ai_family = AF_INET;       /* IPv4 (or AF_INET6 for IPv6)     */
   hints.ai_socktype = SOCK_DGRAM;  /* UDP */
   hints.ai_flags = AI_NUMERICSERV; /* El 'servicio' sera un puerto numerico 'hardcodeado' */

   /* Buscamos una direccion valida del programa pong a quien enviarle nuestro ping 
    * o la direccion del programa ping a quiern responderle con nuestro pong */
   s = getaddrinfo(NULL, (!are_we_a_pong? pong_port : ping_port), &hints, &ptr);

   if (s != 0) { 
     printf("Error in getaddrinfo: %s\n", gai_strerror(s));
     close(skt);
     return -1;
   }

   
   if (are_we_a_pong) {
      // Esperamos el ping
      s = recvfrom(skt, buf, BUF_SIZE, MSG_NOSIGNAL, 0, 0);
      if (s == -1) { 
        printf("Error in recvfrom: %s\n", strerror(errno));
        socket_fail = true;
      }
      print_buf(buf);
      
      // Enviamos el pong
      for (int i = 0; i < 2; ++i) {
        if (!socket_fail) {
          buf[1] = 'O';
          s = sendto(skt, buf, BUF_SIZE, MSG_NOSIGNAL, ptr->ai_addr, ptr->ai_addrlen);
          if (s == -1) { 
            printf("Error in sendto: %s\n", strerror(errno));
            socket_fail = true;
          }
          print_buf(buf);
        }
      }
   }
   else {
      // Enviamos el ping
      s = sendto(skt, buf, BUF_SIZE, MSG_NOSIGNAL, ptr->ai_addr, ptr->ai_addrlen);
      if (s == -1) { 
        printf("Error in sendto: %s\n", strerror(errno));
        socket_fail = true;
      }
      print_buf(buf);

      // Recibimos el pong
      for (int i = 0; i < 2; ++i) {
        if (!socket_fail) {
          s = recvfrom(skt, buf, BUF_SIZE, MSG_NOSIGNAL, 0, 0);
          if (s == -1) { 
            printf("Error in recvfrom: %s\n", strerror(errno));
            socket_fail = true;
          }
          print_buf(buf);
        }
      }
   }

   // Liberamos los recursos
   freeaddrinfo(ptr);
   close(skt);

   return socket_fail? -1 : 0;
}



