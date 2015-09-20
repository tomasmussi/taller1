#include "serverClientProxyAceptador.h"
#include <string>
#include <list>

ClientProxyAceptador::ClientProxyAceptador(std::string puerto)
	: mapa(), socket("localhost", puerto, AI_PASSIVE){
	this->seguir = true;
	this->clientesEliminados = false;
	this->socket.bindSocket();
}

ClientProxyAceptador::~ClientProxyAceptador() {
}

/* Tiene la implementacion de escuchar conexiones entrantes
 * y derivarlas en otro hilo con su socket peer para poder
 * seguir recibiendo conexiones.
 * */
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

/* Envia un mensaje de finalizacion a todos los clientes, no importa
 * lo que esten haciendo. El servidor se esta apagando.
 * */
void ClientProxyAceptador::eliminarClientes(){
	if (!this->clientesEliminados){
		for (std::list<ClientProxy*>::iterator it = threads.begin();
				it != threads.end(); it++){
			(*it)->join();
			delete (*it);
		}
	}
	this->clientesEliminados = true;
}

/* Cierra el socket aceptor y todas las conexiones que fue derivando. */
void ClientProxyAceptador::finalizar(){
	this->seguir = false;
	this->eliminarClientes();
	this->socket.cerrar();
}

void ClientProxyAceptador::run(){
	this->escucharConexiones();
}
