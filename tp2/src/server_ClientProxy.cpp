#include "server_ClientProxy.h"
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>

ClientProxy::ClientProxy(Socket *conexion, MapaConcurrenteHandler *mapa){
	this->conexion = conexion;
	this->mapa = mapa;
	this->finalizado = false;
}

ClientProxy::~ClientProxy() {
}

void ClientProxy::run(){
	std::string mensaje = "";
	conexion->recibir(mensaje);
	while (! this->finMensaje(mensaje) && !finalizado){
		conexion->recibir(mensaje);
	}
	if (!finalizado){
		this->resolverMensaje(mensaje);
	}
	conexion->cerrar();
	delete conexion;
}

bool ClientProxy::finalizar(){
	this->finalizado = true;
	bool fin = conexion->cerrar();
	return fin;
}

bool ClientProxy::finMensaje(std::string mensaje){
	return (mensaje.find("fin\n") != std::string::npos) ||
			((mensaje.find("consultar") != std::string::npos) && (mensaje.find("\n") != std::string::npos));
}

void ClientProxy::resolverMensaje(std::string mensajeString){
	if (mensajeString.find("conector seccion") != std::string::npos){
		MensajeConector mensaje(mensajeString);
		std::string seccion = mensaje.getSeccion();
		while (mensaje.hayActualizacion()){
			Medicion *medicion = mensaje.getMedicionActual();
			mapa->actualizarMedicion(seccion, medicion);
			mensaje.avanzarMedicion();
		}
	} else {
		std::istringstream iss(mensajeString);
		std::vector<std::string> tokens;
		copy(std::istream_iterator<std::string>(iss),
				std::istream_iterator<std::string>(),
				back_inserter(tokens));
		std::string param = tokens.back() == "consultar" ? "" : tokens.back();
		std::string respuesta = mapa->imprimir(param);
		conexion->enviar(respuesta);
	}
}

