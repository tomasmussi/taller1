#include "server_ClientProxyAceptador.h"

ClientProxyAceptador::ClientProxyAceptador(std::string puerto)
	: mapa(), socket("localhost", puerto, AI_PASSIVE){
	this->seguir = true;
	this->clientesEliminados = false;
	this->socket.bindSocket();
}

ClientProxyAceptador::~ClientProxyAceptador() {
}

void ClientProxyAceptador::escucharConexiones(){
	this->socket.listenSocket();
	this->seguir = true;
	while (this->seguir){
		Socket *nuevaConexion = this->socket.aceptar();
		if (this->seguir){
			ClientProxy *proxy = new ClientProxy(nuevaConexion, &mapa);
			threads.push_back(proxy);
			proxy->start();
		} else {
			if (nuevaConexion != NULL){
				delete nuevaConexion;
			}
		}
	}
	this->eliminarClientes();
}

void ClientProxyAceptador::eliminarClientes(){
	if (!this->clientesEliminados){
		for (std::list<ClientProxy*>::iterator it = threads.begin(); it != threads.end(); it++){
			(*it)->join();
			delete (*it);
		}
	}
	this->clientesEliminados = true;
}

void ClientProxyAceptador::finalizar(){
	this->seguir = false;
	this->eliminarClientes();
	this->socket.cerrar();
}

void ClientProxyAceptador::run(){
	this->escucharConexiones();
}



