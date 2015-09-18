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

/**
 * Tengo que cambiar esto.
 * La idea es:
 * Leer 1 linea. Con esto determino el comando
 *  1) Consultar: se resuelve con esta linea, se responde y fin
 *  2) while leer_linea != fin\n, actualizar mapa
 *  Como hacerlo elegante? No tengo la mas puta idea
 *
 * */
void ClientProxy::run(){
	std::string recibido = "";
	bool seguir = true;
	while (seguir && !finalizado){
		recibido = conexion->recibir();
		seguir = this->interpretarEnviado(recibido);
	}
	/*if (!finalizado){
		this->resolverMensaje(recibido);
	}*/
	conexion->cerrar();
	delete conexion;
}

bool ClientProxy::interpretarEnviado(std::string recibido){
	std::cout << "RECIBIDO: " << recibido << std::endl;
	bool seguir = true;
	if (recibido.find("\n") != std::string::npos){
		// Hay un \n, hay que ver que es el mensaje
		std::istringstream iss(recibido);
		std::vector<std::string> tokens;
		std::copy(std::istream_iterator<std::string>(iss),
			 std::istream_iterator<std::string>(),
			 back_inserter(tokens));
		std::cout << "BUFFER: " << buffer << std::endl;
		std::string comando = buffer + recibido;
		buffer.clear();
		std::cout << "BUFFER AFTER " << buffer << std::endl;
		seguir = this->ejecutarComando(comando, true);
		for (size_t i = 1; i < tokens.size(); i++){
			if (tokens[i].find("\n") != std::string::npos){
				seguir = seguir && this->ejecutarComando(tokens[i], false);
			} else {
				//std::cout << "parte: " << i << tokens[i] << std::endl;
				buffer.append(tokens[i]);
			}
		}
	} else {
		std::cout << "BUFFER DEL ELSE : " << buffer << std::endl;
		buffer.append(recibido);
		std::cout << "BUFFER DEL ELSE FIN : " << buffer << std::endl;
	}
	//sleep(1);
	return seguir;
}

bool ClientProxy::ejecutarComando(std::string mensaje, bool primero){
	std::cout << "COMANDO: " << (primero ? " 1) " : " 2) ") << mensaje << std::endl;
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
		/*MensajeConector mensaje(mensaje);
		std::string seccion = mensaje.getSeccion();
		while (mensaje.hayActualizacion()){
			Medicion *medicion = mensaje.getMedicionActual();
			mapa->actualizarMedicion(seccion, medicion);
			mensaje.avanzarMedicion();
		}*/
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

