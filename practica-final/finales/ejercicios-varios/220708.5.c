/*
 *	Ejercicio [5] final 22/07/08
 * 	Escribir un programa que envia datagrama de 20 bytes 'A' al puerto
 * 	202 del equipo 200.49.224.251
 */


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#define BUFFERSIZE 20
#define PORT 220

int main(int argc, char** argv) {
	
	int sockfd;
	struct sockaddr_in theiraddr;
	int bytes_sent = 0;
	struct hostent* he;
	
	if (argc<2) {
		printf("Faltan parametros\n");
		exit(1);
	}
	if ((he=gethostbyname(argv[1])) == NULL) {
    	exit(1);
    }
	/* pido el socket */
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);	
	/* configuro direccion */
	theiraddr.sin_family=AF_INET;
	theiraddr.sin_port=htons(PORT);
	theiraddr.sin_addr = *((struct in_addr *)he->h_addr);
	memset(&(theiraddr.sin_zero), '\0', 8);
	/* ******************* */
	
	/* acciones */
	/* envio paquete a la  direccion */
	bytes_sent = sendto(sockfd,"AAAAAAAAAAAAAAAAAAAA", BUFFERSIZE, 0,
			 (struct sockaddr *)&theiraddr, sizeof(struct sockaddr));
	printf("Bytes enviados: %d\n", bytes_sent);
	if (bytes_sent==-1) {
		close(sockfd);
		return 1;
	}
	while (bytes_sent<BUFFERSIZE) {
		bytes_sent += sendto(sockfd, "AAAAAAAAAAAAAAAAAAAA", BUFFERSIZE, 0,
			 (struct sockaddr *)&theiraddr, sizeof(struct sockaddr));
	}
    close(sockfd);
	return 0;
}
