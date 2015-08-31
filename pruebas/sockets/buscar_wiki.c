/*
   Ejemplo "completo" de uso de sockets:
      - como obtener una direccion IP valida con getaddrinfo
      - como conectarse a un server remoto
      - como enviar y recibir mensajes
      - y como liberar todos los recursos

   El ejemplo esta lleno de comentarios y es bastante "verboso".

   Se compila con 
      gcc -std=c99 -o buscar_wiki buscar_wiki.c 

   Se ejecuta como
      ./buscar_wiki PAGENAME

   donde PAGENAME es el nombre de la wiki que se quiere bajar.
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

/*
   Este es un ejemplo de juguete y por eso usaremos buffers chicos
   y en el stack. Una aplicacion seria manejaria buffers de size
   variable.
*/
#define REQUEST_MAX_LEN 128
#define RESPONSE_MAX_LEN 1024

int main(int argc, char *argv[]) {
   int s = 0;
   bool are_we_connected = false;
   bool is_there_a_socket_error = false;
   bool is_the_remote_socket_closed = false;

   const char *hostname = "es.wikipedia.org";
   const char *servicename = "http";
   
   struct addrinfo hints;
   struct addrinfo *result, *ptr;

   int skt = 0;

   char request[REQUEST_MAX_LEN];
   int request_len;
   char response[RESPONSE_MAX_LEN];

   int bytes_sent = 0;
   int bytes_recv = 0;

   if (argc != 2) return 1; 

   /* Creo una especie de filtro para decir que direcciones me interesan
      En este caso, TCP sobre IPv4 para ser usada por un socket 'activo'
      (no es para un server)
   */ 
   memset(&hints, 0, sizeof(struct addrinfo));
   hints.ai_family = AF_INET;       /* IPv4 (or AF_INET6 for IPv6)     */
   hints.ai_socktype = SOCK_STREAM; /* TCP  (or SOCK_DGRAM for UDP)    */
   hints.ai_flags = 0;              /* None (or AI_PASSIVE for server) */


   /* Obtengo la (o las) direcciones segun el nombre de host y servicio que
      busco
     
      De todas las direcciones posibles, solo me interesan aquellas que sean
      IPv4 y TCP (segun lo definido en hints)
      
      El resultado lo guarda en result
   */
   s = getaddrinfo(hostname, servicename, &hints, &result);

   /* Es muy importante chequear los errores. 
      En caso de uno, usar gai_strerror para traducir el codigo de error (s)
      a un mensaje humanamente entendible.
   */
   if (s != 0) { 
      printf("Error in getaddrinfo: %s\n", gai_strerror(s));
      return 1;
   }

   /* getaddrinfo retorna una **lista** de direcciones. Hay que iterarla
      para encontrar la que mejor se ajusta.
      (generalmente la primera direccion es la mejor, pero dependera de 
      cada caso)

      En este caso voy a probar cada direccion posible. La primera que
      funcione sera la que se usara por el resto del ejemplo.
   */
   for (ptr = result; ptr != NULL && are_we_connected == false; ptr = ptr->ai_next) {
      /* Creamos el socket definiendo la familia (deberia ser AF_INET IPv4),
         el tipo de socket (deberia ser SOCK_STREAM TCP) y el protocolo (0) */
      skt = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
      if (skt == -1) {
         printf("Error: %s\n", strerror(errno));
      }
      else
      {
         /* Nos conectamos a Wikipedia
            ai_addr encapsula la IP y el puerto del server de la Wiki.
            La estructura es automaticamente creada por getaddrinfo */
         s = connect(skt, ptr->ai_addr, ptr->ai_addrlen);
         if (s == -1) {
            printf("Error: %s\n", strerror(errno));
            close(skt);
         }
         are_we_connected = (s != -1); // nos conectamos?
      }
   }

   /* Finalmente, la **lista** de direcciones debe ser liberada */
   freeaddrinfo(result);

   if (are_we_connected == false) {
     return 1; // nos quedamos sin direcciones validas y no nos pudimos conectar :(
   }

   /* Armamos el mensaje HTTP para hablar con Wikipedia.
      Es un mensaje HTTP minimalista, pero sirve.
      Aqui decimos que wiki quiere el usuario leer.
      [Ref http://es.wikipedia.org/wiki/Hypertext_Transfer_Protocol]
    */
   snprintf(request, REQUEST_MAX_LEN, "GET /wiki/%s HTTP/1.1\r\nHost: es.wikipedia.org\r\n\r\n", argv[1]);
   request[REQUEST_MAX_LEN-1] = 0;
   request_len = strlen(request);

   
   /* Enviamos el mensaje intentando enviar todo el mensaje de un solo intento,
      y solo reintentando enviar aquellos bytes que no pudiero entrar */
   while (bytes_sent < request_len && is_there_a_socket_error == false && is_the_remote_socket_closed == false) {
      s = send(skt, &request[bytes_sent], request_len - bytes_sent, MSG_NOSIGNAL);

      if (s < 0) {  // ups,  hubo un error
         printf("Error: %s\n", strerror(errno));
         is_there_a_socket_error = true;
      }
      else if (s == 0) { // nos cerraron el socket :(
         is_the_remote_socket_closed = true;
      }
      else {
         bytes_sent += s;
      }
   }
   
   if (is_the_remote_socket_closed || is_there_a_socket_error) {
      shutdown(skt, SHUT_RDWR);
      close(skt);
      return 1;
   }

   /* 
      Recibimos el mensaje que viene de la Wikipedia.
      Para simplificar, vamos a leer hasta que el server nos cierre la coneccion.
      (no es para nada optimo, pero es mas simple)
   */
   while (is_there_a_socket_error == false && is_the_remote_socket_closed == false) {
      s = recv(skt, &response[bytes_recv], RESPONSE_MAX_LEN - bytes_recv - 1, MSG_NOSIGNAL);

      if (s < 0) {
         printf("Error: %s\n", strerror(errno));
         is_there_a_socket_error = true;
      }
      else if (s == 0) {
         // cerraron el socket del otro lado:
         // voy a asumir que nos dieron toda la respuesta (estoy simplificando esto)
         is_the_remote_socket_closed = true;
      }
      else {
         bytes_recv = s; 

         response[bytes_recv] = 0;
         printf("%s", response);

         //reusamos el mismo buffer, no me interesa tener toda la 
         //respuesta en memoria
         bytes_recv = 0; 
      }
   }

   /* Le decimos a la otra maquina que cerramos la coneccion */
   shutdown(skt, SHUT_RDWR);

   /* Cerramos el socket */
   close(skt);

   if (is_there_a_socket_error) {
      return 1;   // hubo un error, somos consistentes y salimos con un codigo de error
   }
   else {
      return 0;
   }
}

