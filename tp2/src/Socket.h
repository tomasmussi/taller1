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
	struct sockaddr *ai_addr;
	bool conectado;

public:

	Socket(std::string ip, std::string puerto);
	~Socket();
	bool conectar();
	bool enviar(std::string mensaje);
};

#endif /* SRC_SOCKET_H_ */
