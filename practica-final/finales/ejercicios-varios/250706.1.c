/*
 * 		Ejercicio [1] final 25/07/06
 * 		Escriba un pequeno programa que acepte una unica conexion TCP
 * 		en el puerto 1120, reciba paquetes de 32bytes y los devuelva.
 * 		El programa debe terminar al recibir un paquete de 32 bytes
 * 		de '\0'		
 */


#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>

#define PORT 1120
#define BACKLOG 5
#define BUFFERSIZE 32

int analyzebuffer( char* buf ) {
	int i=0;
	int allZeros=1;
	printf("BUFFER: %s\n", buf);
	
	for (i=0; i<BUFFERSIZE; i++){
		if (buf[i]!='\0') {
			allZeros=0;
			break;
		}
	}
	return allZeros;
}

int main(int argc, char** argv)
{
	int sockfd;
	int new_fd;
	struct sockaddr_in myaddr;
	struct sockaddr_in theiraddr;
	int end = 0;
	int sin_size=sizeof(struct sockaddr_in);
	int len = 0;
	char buffer[BUFFERSIZE];
	int bytes_rcvd = 0;
	int bytes_sent = 0;
		
	
	/* pido el socket */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);	
	/* configuro para reusar puerto bloqueado */
	int yes = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
	/* configuro direccion */
	myaddr.sin_family=AF_INET;
	myaddr.sin_port=htons(PORT);
	myaddr.sin_addr.s_addr=INADDR_ANY; /* mi IP */
	memset(&(myaddr.sin_zero), '\0', 8);
	/* ******************* */
	
	/* acciones */
	bind(sockfd, (struct sockaddr*)&myaddr, sizeof(struct sockaddr));
	listen(sockfd, BACKLOG);
	while (1){
	new_fd=accept(sockfd, (struct sockaddr*)&theiraddr,&sin_size);
		if (new_fd!=-1) {
			close(sockfd); /* no escucho mas conexiones */
			break;
		}
	}
	while (!end) {
		
		/* recibo paquete */
		
		bytes_rcvd = recv(new_fd, buffer, BUFFERSIZE, 0);
		while (bytes_rcvd<BUFFERSIZE) {
			bytes_rcvd += recv(new_fd, buffer, BUFFERSIZE, 0);
		}
		/* imprimo el paquete de 32b que recibi */
		printf("%s\n", buffer);
		/* no recibi 32 '\0' */
		if (!analyzebuffer(buffer)) {
			/* envio el mismo paquete */
			bytes_sent = send(new_fd, buffer, strlen(buffer), 0);
			while (bytes_sent<BUFFERSIZE) {
				bytes_sent += send(new_fd, buffer, strlen(buffer), 0);	
			}			
		} else /* salgo */
			end = 1;
	}
	return 0;
}
