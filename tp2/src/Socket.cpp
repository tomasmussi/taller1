#include "Socket.h"


Socket::Socket (std::string ip, std::string puerto) {
	struct addrinfo hints;
	struct addrinfo *posibilidades, *iterador;

	this->conectado = false;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = 0;
	int resultado = getaddrinfo(ip.c_str(), puerto.c_str(), &hints, &posibilidades);
	if (resultado != 0){
		std::cerr << "ERROR EN ADDRINFO: " << gai_strerror(resultado) << std::endl;
		return;
	}
	iterador = posibilidades;
	bool direccionNoValida = true;
	int skt;
	while (iterador != NULL && direccionNoValida){
		skt = socket(iterador->ai_family, iterador->ai_socktype, iterador->ai_protocol);
		//skt = socket(iterador->ai_family, iterador->ai_socktype, iterador->ai_protocol);
		if (skt != -1){
			// Anduvo, nos podemos conectar a esta direccion
			this->socketFD = skt;
			this->ai_addr = iterador->ai_addr;
			this->ai_addrlen = iterador->ai_addrlen;
			direccionNoValida = false;
		}
		iterador = iterador->ai_next;
	}
	freeaddrinfo(posibilidades);
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

Socket::~Socket() {
	shutdown(this->socketFD, SHUT_RDWR);
	close(this->socketFD);
}

