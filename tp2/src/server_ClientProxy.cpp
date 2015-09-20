#include "server_ClientProxy.h"
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
#include <unistd.h>

ClientProxy::ClientProxy(Socket *conexion, MapaConcurrenteHandler *mapa){
	this->conexion = conexion;
	this->mapa = mapa;
	this->finalizado = false;
	this->buffer = "";
	this->seccion = "";
}

ClientProxy::~ClientProxy() {
}

void ClientProxy::run(){
	std::string recibido = "";
	bool seguir = true;
	while (seguir && !finalizado){
		recibido = conexion->recibir();
		seguir = this->interpretarEnviado(recibido);
	}
	conexion->cerrar();
	delete conexion;
}

bool ClientProxy::interpretarEnviado(std::string recibido){
	bool seguir = true;
	if (recibido.find("\n") != std::string::npos){
		// Hay un \n, hay que ver que es el mensaje
		std::istringstream iss(recibido);
		std::string comando;
		std::getline(iss, comando, '\n');
		comando = buffer + comando;
		buffer.clear();
		while (!iss.eof()){
			seguir = seguir && this->ejecutarComando(comando);
			std::getline(iss, comando, '\n');
		}
		buffer.append(comando);
	} else {
		buffer.append(recibido);
	}
	return seguir;
}

bool ClientProxy::ejecutarComando(std::string mensaje){
	if (mensaje.find("consultar") == std::string::npos){
		if (mensaje.find("conector") != std::string::npos){
			// Es conector
			std::stringstream ss(mensaje);
			std::string seccion;
			ss >> seccion;
			ss >> seccion;
			ss >> seccion;
			this->seccion = seccion;
		} else if (mensaje.find("actualizar") != std::string::npos){
			// Es actualizacion
			std::stringstream parcial(mensaje);
			std::string medicion;
			int nivel, caudal;
			parcial >> medicion; // actualizar
			parcial >> medicion; // nivel
			parcial >> nivel; // numero
			parcial >> medicion; // caudal
			parcial >> caudal;
			mapa->actualizarMedicion(seccion, new Medicion(nivel, caudal));
		}
	} else {
		std::istringstream iss(mensaje);
		std::vector<std::string> tokens;
		copy(std::istream_iterator<std::string>(iss),
				std::istream_iterator<std::string>(),
				back_inserter(tokens));
		std::string param = tokens.back() == "consultar" ? "" : tokens.back();
		std::string respuesta = mapa->imprimir(param);
		conexion->enviar(respuesta);
	}
	return !this->finMensaje(mensaje);
}

bool ClientProxy::finalizar(){
	this->finalizado = true;
	bool fin = conexion->cerrar();
	return fin;
}

bool ClientProxy::finMensaje(std::string mensaje){
	return (mensaje.find("fin") != std::string::npos) ||
			(mensaje.find("consultar") != std::string::npos);
}
