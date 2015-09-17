#include "server_ClientProxyAceptador.h"

ClientProxyAceptador::ClientProxyAceptador(std::string puerto){
	this->seguir = true;
	this->clientesEliminados = false;
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
	while (this->seguir){
		Socket *nuevaConexion = this->socket->aceptar();
		if (this->seguir){
			ClientProxy *proxy = new ClientProxy(nuevaConexion, mapa);
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
	//std::cout << "FINALIZAR CLIENTPROXYACEPTADOR\n";
	this->seguir = false;
	this->eliminarClientes();
	this->socket->cerrar();
	//std::cout << "DONE CLIENTPROXYACEPTADOR\n";
}

void ClientProxyAceptador::run(){
	this->escucharConexiones();
}



