/*
   Ejemplo de un echo server.
   Este ejemplo TIENE UN BUG (en realidad son 2 combinados).

   La idea de un echo server es la siguiente:
      1) El cliente se conecta a este server y le envia un numero 
         de 2 digitos (en texto) que representa la longitud del 
         mensaje que le sigue.
      2) El cliente luego envia ese mensaje de esa longitud
      3) El server lee ese mensaje y luego se lo reenvia al cliente.

   Se compila con 
      gcc -std=c99 -o echoserver echoserver.c 

   Se ejecuta como
      ./echoserver PORT PASSWORD

   donde PORT es el nombre de un servicio ("http" por ejemplo) o el numero
   de puerto directamente (80 por ejemplo) 
   PASSWORD es un string que representa algo secreto. No tiene nada que
   ver con el echo server y es borrado de la memoria con free
   Asi que no deberia haber ningun problema en, por ejemplo, que pongas 
   tu password de facebook/clave bancaria, no?
*/


#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 1
#endif

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>


int recv_message(int skt, char *buf, int size) {
   int received = 0;
   int s = 0;
   bool is_the_socket_valid = true;

   while (received < size && is_the_socket_valid) {
      s = recv(skt, &buf[received], size-received, MSG_NOSIGNAL);
      
      if (s == 0) { // nos cerraron el socket :(
         is_the_socket_valid = false;
      }
      else if (s < 0) { // hubo un error >(
         is_the_socket_valid = false;
      }
      else {
         received += s;
      }
   }

   if (is_the_socket_valid) {
      return received;
   }
   else {
      return -1;
   }
}

int send_message(int skt, char *buf, int size) {
   int sent = 0;
   int s = 0;
   bool is_the_socket_valid = true;

   while (sent < size && is_the_socket_valid) {
      s = send(skt, &buf[sent], size-sent, MSG_NOSIGNAL);
      
      if (s == 0) {
         is_the_socket_valid = false;
      }
      else if (s < 0) {
         is_the_socket_valid = false;
      }
      else {
         sent += s;
      }
   }

   if (is_the_socket_valid) {
      return sent;
   }
   else {
      return -1;
   }
}


/*
   Hacemos un procesamiento a un password y usamos
   el heap a toda maquina.
   Liberamos la memoria asi no tenemos ningun problema, no? 
                                                que podria salir mal? 
*/
#define REPEATS 16   //agregar mas repeticiones si es necesario
void process(char *password) {
   int i;

   const char *msg = "Your secret password is: %s!";
   int msg_len = strlen(msg) - 2; // no contar el "%s" (2 bytes)
   int password_len = strlen(password);

   char *buf[REPEATS];
   int buf_size = password_len + msg_len + 1;

   for (i = 0; i < REPEATS; ++i) {
      buf[i] = (char*) malloc(sizeof(char) * buf_size);
   
      snprintf(buf[i], buf_size, msg, password);
      buf[i][buf_size-1] = 0;
   }

   for (i = 0; i < REPEATS; ++i) {
      free(buf[i]);
   }
}

#define MAX_SMALL_BUF_LEN 3   //2 bytes

int main(int argc, char *argv[]) {
   int s = 0;
   unsigned short len = 0;
   bool continue_running = true;
   bool is_the_accept_socket_valid = true;
   
   struct addrinfo hints;
   struct addrinfo *ptr;

   int skt, peerskt = 0;

   char small_buf[MAX_SMALL_BUF_LEN];
   char *tmp;

   if (argc != 3) return 1; 

   process(argv[2]);

   memset(&hints, 0, sizeof(struct addrinfo));
   hints.ai_family = AF_INET;       /* IPv4 (or AF_INET6 for IPv6)     */
   hints.ai_socktype = SOCK_STREAM; /* TCP  (or SOCK_DGRAM for UDP)    */
   hints.ai_flags = AI_PASSIVE;     /* AI_PASSIVE for server           */

   s = getaddrinfo(NULL, argv[1], &hints, &ptr);

   if (s != 0) { 
      printf("Error in getaddrinfo: %s\n", gai_strerror(s));
      return 1;
   }

   skt = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

   if (skt == -1) {
      printf("Error: %s\n", strerror(errno));
      freeaddrinfo(ptr);
      return 1;
   }

   // Decimos en que direccion local queremos escuchar, en especial el puerto
   // De otra manera el sistema operativo elegiria un puerto random
   // y el cliente no sabria como conectarse
   s = bind(skt, ptr->ai_addr, ptr->ai_addrlen);
   if (s == -1) {
      printf("Error: %s\n", strerror(errno));
      close(skt);
      freeaddrinfo(ptr);
      return 1;
   }

   freeaddrinfo(ptr);

   // Cuanto clientes podemos mantener en espera antes de poder acceptarlos?
   s = listen(skt, 20);
   if (s == -1) {
      printf("Error: %s\n", strerror(errno));
      close(skt);
      return 1;
   }

   while (continue_running) {
      peerskt = accept(skt, NULL, NULL);   // aceptamos un cliente
      if (peerskt == -1) {
         printf("Error: %s\n", strerror(errno));
         continue_running = false;
         is_the_accept_socket_valid = false;
      }
   
      else {
         printf("New client\n");
         memset(small_buf, 0, MAX_SMALL_BUF_LEN);
         recv_message(peerskt, small_buf, MAX_SMALL_BUF_LEN-1); 
         
         len = atoi(small_buf);
         printf("Echo %i bytes\n", len);

         if (len == 0) {
            printf("Zero bytes. Bye!\n");
            continue_running = false;
         }

         else {
            tmp = (char*) malloc(sizeof(char) * len);

            // XXX my heart is bleeding
            printf("Received %i/%i bytes\n", recv_message(peerskt, tmp, len), len);
            printf("Sent %i/%i bytes\n\n", send_message(peerskt, tmp, len), len);
            free(tmp);
         }

         shutdown(peerskt, SHUT_RDWR);
         close(peerskt);
      }
   }
   
   shutdown(skt, SHUT_RDWR);
   close(skt);

   if (is_the_accept_socket_valid) {
      return 1;
   } 
   else { 
      return 0;
   }
}
