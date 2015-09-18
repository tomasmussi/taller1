#ifndef SRC_SOCKET_H_
#define SRC_SOCKET_H_

#include <string>
#include <iostream>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>


class Socket {

private:
	int socketFD;
	socklen_t ai_addrlen;
	struct sockaddr ai_addr;
	bool conectado;
	bool cerrado;
	bool enviar(const char *buffer, ssize_t tamanio);
	bool recibir(char *buffer, int tamanio);

public:

	Socket(std::string ip, std::string puerto, int flags);
	Socket(int nuevoSocketFD);
	~Socket();
	bool bindSocket();
	bool listenSocket();
	Socket* aceptar();
	bool conectar();
	bool enviar(std::string mensaje);
	bool recibir(std::string &mensaje);
	bool cerrar();
};

#endif /* SRC_SOCKET_H_ */
