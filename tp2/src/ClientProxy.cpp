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
		std::cout << mensaje << std::endl;
		mensaje.clear();
		mensaje = nuevaConexion->recibir();
		std::cout << mensaje << std::endl;
		mensaje.clear();
		mensaje = nuevaConexion->recibir();
		std::cout << mensaje << std::endl;
		mensaje.clear();
		std::string fin = nuevaConexion->recibir();
		std::cout << fin << std::endl;
		if (fin == "fin"){
			std::cout << "se puede comparar asi\n";
		}
		if (strcmp(fin.c_str(),"fin") == 0){
			std::cout << "strcmp\n";
		}
		/*std::cout << "mensaje != fin " << (mensaje != "fin") << std::endl;
		std::cout << "mensaje != fin " << (mensaje.compare("fin")) << std::endl;
		std::cout << "compare " << (strcmp(mensaje.c_str(), "fin") == 0) << std::endl;*/
		/*while (mensaje != "fin"){
			mensaje = nuevaConexion->recibir();
			std::cout << mensaje << std::endl;
		}
		std::cout << mensaje << std::endl;*/
		delete nuevaConexion;
	}
}
