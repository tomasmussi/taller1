#include "Socket.h"
#include <unistd.h>
#include <stdlib.h>

#define MAX_CONEXIONES 20
#define MAX_BUFFER 100

Socket::Socket (std::string ip, std::string puerto, int flags) {
	struct addrinfo hints;
	struct addrinfo *posibilidades, *iterador;
	this->conectado = false;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET; /* IP v4*/
	hints.ai_socktype = SOCK_STREAM; /* Protocolo TCP */
	hints.ai_flags = flags;
	int resultado = getaddrinfo(ip.c_str(), puerto.c_str(), &hints, &posibilidades);
	if (resultado != 0){
		std::cerr << "ERROR EN ADDRINFO: " << gai_strerror(resultado) << std::endl;
		return;
	}
	iterador = posibilidades;
	bool direccionNoValida = true;
	while (iterador != NULL && direccionNoValida){
		int skt = socket(iterador->ai_family, iterador->ai_socktype, iterador->ai_protocol);
		if (skt != -1){
			// Anduvo, nos podemos conectar a esta direccion
			this->socketFD = skt;
			this->ai_addr = (struct sockaddr*) malloc(sizeof(struct sockaddr));
			memcpy(this->ai_addr, iterador->ai_addr, sizeof(struct sockaddr));
			this->ai_addrlen = iterador->ai_addrlen;
			direccionNoValida = false;
		}
		iterador = iterador->ai_next;
	}
	if (direccionNoValida){
		std::cerr << "NO SE OBTUVIERON DIRECCIONES VALIDAS" << std::endl;
	}
	freeaddrinfo(posibilidades);
}

Socket::Socket(int nuevoSocketFD){
	this->socketFD = nuevoSocketFD;
	this->ai_addr = NULL;
	memset(&this->ai_addrlen, 0, sizeof(socklen_t));
	this->conectado = true;
}

bool Socket::bindSocket(){
	int resultado = bind(this->socketFD, this->ai_addr, this->ai_addrlen);
	if (resultado != 0){
		std::cerr << "ERROR AL BINDEAR SOCKET: " << gai_strerror(resultado) << std::endl;
		return false;
	}
	return true;
}

bool Socket::conectar(){
	int resultado = connect(this->socketFD, this->ai_addr, this->ai_addrlen);
	this->conectado = resultado == 0;
	if (resultado != 0){
		std::cerr << "ERROR AL CONECTAR: " << gai_strerror(resultado) << std::endl;
		close(this->socketFD);
		return false;
	}
	return true;
}

Socket* Socket::aceptar(){
	int nuevoSocketFD = accept(this->socketFD, NULL, NULL);
	if (nuevoSocketFD == -1){
		std::cerr << "ERROR AL ACEPTAR CONEXION. " << gai_strerror(nuevoSocketFD) << std::endl;
		return NULL;
	}
	return new Socket(nuevoSocketFD);
}

bool Socket::listenSocket(){
	int resultado = listen(this->socketFD, MAX_CONEXIONES);
	if (resultado != 0){
		std::cerr << "ERROR AL ESCUCHAR SOCKET: " << gai_strerror(resultado) << std::endl;
		return false;
	}
	return true;
}

bool Socket::enviar(std::string mensaje){
	if (!this->conectado){
		return false;
	}
	const char *buffer = mensaje.c_str();
	size_t longitudMensaje = mensaje.length();
	size_t bytesEnviados = 0;
	bool error = false, socketCerrado = false;
	while (bytesEnviados < longitudMensaje && !error && !socketCerrado){
		int envioParcial = send(this->socketFD, buffer, longitudMensaje, MSG_NOSIGNAL);
		if (envioParcial < 0){
			std::cerr << "ERROR AL ENVIAR MENASJE: " << mensaje << ". ERROR: " << gai_strerror(envioParcial) << std::endl;
			error = true;
		} else if (envioParcial == 0){
			std::cerr << "SOCKET CERRADO DESDE EL OTRO PUNTO. " << std::endl;
			socketCerrado = true;
		} else {
			bytesEnviados += envioParcial;
		}
	}
	if (error || socketCerrado){
		this->conectado = false;
		shutdown(this->socketFD, SHUT_RDWR);
		close(this->socketFD);
		return false;
	}
	return true;
}

std::string Socket::recibir(){
	int bytesRecibidos = 0;
	char buffer[MAX_BUFFER];
	memset(buffer, 0, MAX_BUFFER);
	// Leo hasta un maximo de MAX_BUFFER caracteres
	bool error = false, socketCerrado = false;
	bool termino = false;
	while (bytesRecibidos < MAX_BUFFER && !error && !socketCerrado && !termino){
		int recibidoParcial = recv(this->socketFD, buffer + bytesRecibidos, MAX_BUFFER, MSG_NOSIGNAL);
		if (recibidoParcial < 0){
			std::cerr << "ERROR AL RECIBIR MENSAJE: " << gai_strerror(recibidoParcial) << std::endl;
			error = true;
		} else if (recibidoParcial == 0){
			std::cerr << "SOCKET CERRADO DESDE EL OTRO PUNTO. " << std::endl;
			socketCerrado = true;
		} else {
			for (int i = bytesRecibidos; (i < (bytesRecibidos + recibidoParcial)) && !termino; i++){
				if (buffer[i] == '\n'){
					termino = true;
				}
				if (termino){
					std::cout << "FIN: " << "char: " << ((buffer[i] == '\n') ? "barraene" : "") << std::endl;
				}
			}
			bytesRecibidos += recibidoParcial;
		}
	}
	if (error || socketCerrado){
		shutdown(this->socketFD, SHUT_RDWR);
		close(this->socketFD);
		return "";
	}

	buffer[bytesRecibidos - 1] = '\0';
	if (strcmp(buffer, "fin") == 0){
		std::cout << "Mensaje: " << buffer << std::endl;
		std::cout << "bytes: " << bytesRecibidos << std::endl;
	}
	return std::string(buffer);
}

Socket::~Socket() {
	free(this->ai_addr);
	shutdown(this->socketFD, SHUT_RDWR);
	close(this->socketFD);
}

