/*
9)
Escriba un pequeño programa que, sin validar errores, acepte una única conexión TCP en el puerto 1972 y 
* reciba paquetes de no mas de 600 bytes, terminado en '0x00'. 
* Cada paquete recibido debe ser devuelto con todos sus bits negados. 
* Terminar al recibir un paquete nulo.

gcc -ansi -std=c99 -o echo ej9.c

*/

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 1
#endif

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#define MAX 600
#define NULO 0x00

void enviar(int socket, const char *buffer, ssize_t len) {
	ssize_t enviado = 0;
	while (enviado < len) {
		enviado += send(socket, buffer + enviado, len - enviado, MSG_NOSIGNAL);
	}
}

void negar(char *buffer, ssize_t len) {
	for (ssize_t i = 0; i < len; i++){
		buffer[i] = !buffer[i];
	}
}

bool seguir_leyendo(const char *buffer, ssize_t leido) {
	for (ssize_t c = 0; c < leido; c++) {
		if (buffer[c] == NULO)
			return false;
	}
	return true;
}

ssize_t interpretar(int socket, char *buffer) {
	ssize_t leido = 0;
	bool keep = true;
	while (keep && leido < MAX) {
		leido += recv(socket, buffer + leido, MAX - leido, MSG_NOSIGNAL);
		keep = seguir_leyendo(buffer, leido);
	}
	return leido;
}

bool leer(int skt) {
	char buffer[MAX];
	ssize_t leido = 0;
	bool seguir = true;
	while (seguir) {
		ssize_t leido = interpretar(skt, buffer);
		negar(buffer, leido);
		enviar(skt, buffer, leido);
		seguir = buffer[0] == NULO && leido == 1;
	}
	
}

void server() {
	struct addrinfo hints;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET; // IPv4
	hints.ai_socktype = SOCK_STREAM; // TCP
	hints.ai_flags = AI_PASSIVE; // Server
	struct addrinfo *results;
	getaddrinfo("localhost", "1972", &hints, &results);
	
	int a = results->ai_family;
	int b = results->ai_socktype;
	int c = results->ai_protocol;
	
	int skt = socket(a, b, c);
	bind(skt, results->ai_addr, results->ai_addrlen);
	freeaddrinfo(results);
	listen(skt, 20);
	bool keep_running = true;

	int peer_skt = accept(skt, NULL, NULL);
	leer(peer_skt);	
	shutdown(peer_skt, SHUT_RDWR);
	close(peer_skt);
	shutdown(skt, SHUT_RDWR);
	close(skt);
}

void imprimir(char *pre, char *post, size_t len) {
	for (size_t l = 0; l < len; l++) {
		printf("comparo: pre[%zd] contra post[%zd]: %c = %c\n", l, l, pre[l], post[l]);
	}
}

void cliente(const char *puerto) {
	struct addrinfo hints;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = 0;
	struct addrinfo *ptr;
	getaddrinfo("localhost", puerto, &hints, &ptr);
	int skt = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
	connect(skt, ptr->ai_addr, ptr->ai_addrlen);
	freeaddrinfo(ptr);
	
	char buffer[MAX];
	char lectura[MAX];
	buffer[0] = 'a';
	buffer[1] = 'b';
	buffer[2] = 'b';
	buffer[3] = NULO;
	
	send(skt, buffer, 4, MSG_NOSIGNAL); //  Me la estoy jugando
	recv(skt, lectura, 4, MSG_NOSIGNAL);
	bool ok = true;
	for (int i = 0; i < 4; i++) {
		ok &= lectura[i] == (!buffer[i]);
	}
	printf("Por ahora: %s\n", ok ? "OK" : "ERROR");
	
	
	buffer[0] = 'd';
	buffer[1] = 'e';
	buffer[2] = 'f';
	buffer[3] = 'g';
	buffer[4] = 'f';
	buffer[5] = 'f';	
	buffer[6] = NULO;
	send(skt, buffer, 7, MSG_NOSIGNAL); //  Me la estoy jugando
	recv(skt, lectura, 7, MSG_NOSIGNAL);
	imprimir(buffer, lectura, 7);
	for (int i = 0; i < 7; i++) {
		ok &= lectura[i] == (!buffer[i]);
	}
	printf("Por ahora: %s\n", ok ? "OK" : "ERROR");
	
	
	buffer[0] = NULO;
	send(skt, buffer, 1, MSG_NOSIGNAL); //  Me la estoy jugando
	recv(skt, lectura, 1, MSG_NOSIGNAL);
	imprimir(buffer, lectura, 1);
	ok = (lectura[0] == (!buffer[0]));
	printf("Final: %s\n", ok ? "OK" : "ERROR");
	shutdown(skt, SHUT_RDWR);
	close(skt);
}


int main(int argc, char *argv[]) {
	if (argc > 1) {
		cliente(argv[1]);
	} else {
		server();
	}
	return 0;
}

