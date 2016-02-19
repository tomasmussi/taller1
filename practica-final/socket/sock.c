
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 1
#endif



#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#include <stdbool.h>
#include <string.h>
#include <stdio.h>


void env(int skt, const char *buffer, ssize_t len) {
	ssize_t enviado = 0;
	bool fin = false;
	while (enviado < len && !fin) {
		ssize_t parcial = send(skt, buffer + enviado, len - enviado, MSG_NOSIGNAL);
		if (parcial <= 0)
			fin = true;
		else
			enviado += parcial;
	}
}


int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Especificar host y puerto");
		return 1;
	}
	struct addrinfo hints;
	struct addrinfo *rtas;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET; // IPv4
	hints.ai_socktype = SOCK_STREAM; // TCP

	getaddrinfo(argv[1], argv[2], &hints, &rtas);
	int skt = socket(rtas->ai_family, rtas->ai_socktype, rtas->ai_protocol);
	connect(skt, rtas->ai_addr, rtas->ai_addrlen);
	freeaddrinfo(rtas);

	char *buffer = "Soy Tomas el mas crack de todos los tiempos.\n";
	size_t len = strlen(buffer);
	env(skt, buffer, len);
	printf("Enviado!\n");
	shutdown(skt, SHUT_RDWR);
	close(skt);
	return 0;
}
	

