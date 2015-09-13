#include "ClientProxy.h"
#include "MensajeConector.h"
#include <iostream>

ClientProxy::ClientProxy(std::string puerto) {
	this->seguir = true;
	this->secciones = new std::map<std::string, Medicion*>();
	std::string localhost("localhost");
	this->socket = new Socket(localhost, puerto, AI_PASSIVE);
	this->socket->bindSocket();
}

ClientProxy::~ClientProxy() {
	for (std::map<std::string, Medicion*>::iterator it = this->secciones->begin(); it != this->secciones->end(); it++){
		delete it->second;
	}
	delete this->secciones;
	delete this->socket;
}

bool ClientProxy::finMensaje(std::string mensaje){
	return mensaje.find("fin") != std::string::npos || mensaje.find("consultar\n") != std::string::npos;
}

void ClientProxy::escucharConexiones(){
	this->socket->listenSocket();
	this->seguir = true;
	while (this->seguir){
		Socket *nuevaConexion = this->socket->aceptar();
		std::string mensaje = nuevaConexion->recibir();
		while (! this->finMensaje(mensaje)){
			mensaje += nuevaConexion->recibir();
		}
		this->resolverMensaje(mensaje);
		this->imprimir();
		delete nuevaConexion;
	}
}

void ClientProxy::finalizar(){
	std::cout << "llega finalizar\n";
	this->seguir = false;
}

void ClientProxy::run(){
	this->escucharConexiones();
}

void ClientProxy::resolverMensaje(std::string mensajeString){
	/* Por el momento solo resuelvo los conectores */
	MensajeConector mensaje(mensajeString);
	std::string seccion = mensaje.getSeccion();
	while (mensaje.hayActualizacion()){
		Medicion *medicion = mensaje.getMedicionActual();
		this->actualizarMedicion(seccion, medicion);
		mensaje.avanzarMedicion();
	}
}

void ClientProxy::actualizarMedicion(std::string seccion, Medicion *medicion){
	if (this->secciones->find(seccion) != this->secciones->end()){
		delete (*this->secciones)[seccion];
	}
	(*this->secciones)[seccion] = medicion;
}

void ClientProxy::imprimir(){
	for (std::map<std::string, Medicion*>::iterator it = this->secciones->begin(); it != this->secciones->end(); it++){
		std::cout << "seccion " << it->first << " nivel " << it->second->getNivel() << " caudal " << it->second->getCaudal() << "\n";
	}
}
