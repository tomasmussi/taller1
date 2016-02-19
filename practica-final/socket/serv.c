#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 1
#endif



#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void rec(int socket, char *buffer, ssize_t len) {
	memset(buffer, 0, len);
	ssize_t recibido = 0;
	bool fin = false;
	while (recibido < len && !fin) {
		ssize_t parc = recv(socket, buffer + recibido, len - recibido, MSG_NOSIGNAL);
		if (parc <=0)
			fin = true;
		else
			recibido += parc;
	}
}


int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Debe especificar puerto\n");
		return 1;
	}

	struct addrinfo hints;
	struct addrinfo *rtas;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	getaddrinfo(NULL, argv[1], &hints, &rtas);
	int skt = socket(rtas->ai_family, rtas->ai_socktype, rtas->ai_protocol);
	bind(skt, rtas->ai_addr, rtas->ai_addrlen);
	freeaddrinfo(rtas);
	listen(skt, 20);
	int skt_peer = accept(skt, NULL, NULL);
	char buffer[1024];
	rec(skt_peer, buffer, 1024);
	buffer[1023] = '\0';
	printf("Recibido: %s\n", buffer);
	shutdown(skt_peer, SHUT_RDWR);
	close(skt_peer);
	shutdown(skt, SHUT_RDWR);
	close(skt);

	return 0;
}
