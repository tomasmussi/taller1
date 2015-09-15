#include "ClientProxyAceptador.h"
#include "ClientProxy.h"
#include <list>

ClientProxyAceptador::ClientProxyAceptador(std::string puerto){
	this->seguir = true;
	this->mapa = new MapaConcurrenteHandler();
	std::string localhost("localhost");
	this->socket = new Socket(localhost, puerto, AI_PASSIVE);
	this->socket->bindSocket();
}

ClientProxyAceptador::~ClientProxyAceptador() {
	delete this->mapa;
	delete this->socket;
}

void ClientProxyAceptador::escucharConexiones(){
	this->socket->listenSocket();
	this->seguir = true;
	std::list<ClientProxy*> threads;
	while (this->seguir){
		Socket *nuevaConexion = this->socket->aceptar();
		ClientProxy *proxy = new ClientProxy(nuevaConexion, mapa);
		threads.push_back(proxy);
		proxy->start();
	}
	for (std::list<ClientProxy*>::iterator it = threads.begin(); it != threads.end(); it++){
		(*it)->join();
		delete (*it);
	}
}

void ClientProxyAceptador::finalizar(){
	this->seguir = false;
}

void ClientProxyAceptador::run(){
	this->escucharConexiones();
}



