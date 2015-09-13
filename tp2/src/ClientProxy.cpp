#include "ClientProxy.h"
#include <iostream>

ClientProxy::ClientProxy(std::string puerto) {
	std::string localhost("localhost");
	this->socket = new Socket(localhost, puerto, AI_PASSIVE);
	this->socket->bindSocket();
}

ClientProxy::~ClientProxy() {
	delete this->socket;
}

void ClientProxy::escucharConexiones(){
	this->socket->listenSocket();
	bool seguir = true;
	while (seguir){
		Socket *nuevaConexion = this->socket->aceptar();
		std::string mensaje = nuevaConexion->recibir();
		while (mensaje.find("fin") == std::string::npos){
			mensaje += nuevaConexion->recibir();
		}
		std::cout << mensaje;
		delete nuevaConexion;
	}
}
