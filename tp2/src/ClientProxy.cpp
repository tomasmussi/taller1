#include "ClientProxy.h"
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>

ClientProxy::ClientProxy(Socket *conexion, MapaConcurrenteHandler *mapa){
	this->conexion = conexion;
	this->mapa = mapa;
}

ClientProxy::~ClientProxy() {
}

void ClientProxy::run(){
	std::string mensaje = "";
	conexion->recibir(mensaje);
	while (! this->finMensaje(mensaje)){
		conexion->recibir(mensaje);
	}
	this->resolverMensaje(mensaje);
	delete conexion;
}

bool ClientProxy::finMensaje(std::string mensaje){
	return mensaje.find("fin\n") != std::string::npos ||
			(mensaje.find("consultar") != std::string::npos && mensaje.find("\n"));
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
		/*for (std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); it++){
			std::cout << *it << std::endl;
		}*/
		std::string param = tokens.back() == "consultar" ? "" : tokens.back();
		std::string respuesta = mapa->imprimir(param);
		conexion->enviar(respuesta);
	}

}
