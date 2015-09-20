#include "serverClientProxy.h"
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
#include <unistd.h>

/* Representa una conexion con uno de los clientes(sensores) del rio */
ClientProxy::ClientProxy(Socket *conexion, MapaConcurrenteHandler *mapa){
	this->conexion = conexion;
	this->mapa = mapa;
	this->finalizado = false;
	this->buffer = "";
	this->seccion = "";
}

ClientProxy::~ClientProxy() {
}

/* Se ejecuta en un hilo separado al del Socket que acepta conexiones,
 * por eso tiene su propio Socket peer y el mapa que hay que actualizar.
 * */
void ClientProxy::run(){
	std::string recibido = "";
	bool seguir = true;
	while (seguir && !finalizado){
		recibido = conexion->recibir();
		seguir = this->interpretarRecibido(recibido);
	}
	conexion->cerrar();
	delete conexion;
}

/* Interpreta los bytes recibidos de la conexion y arma los comandos a
 * ejecutar.
 * */
bool ClientProxy::interpretarRecibido(std::string recibido){
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

/* El socket aceptor envia una senial de terminacion porque se quiere finalizar
 * el servidor, eso implica cerrar todas las conexiones con los clientes.
 * Se marca como finalizado y se cierra la conexion con la otra punta
 * */
bool ClientProxy::finalizar(){
	this->finalizado = true;
	bool fin = conexion->cerrar();
	return fin;
}

/* Verifica si el comando es para finalizar la conexion. */
bool ClientProxy::finMensaje(std::string comando){
	return (comando.find("fin") != std::string::npos) ||
			(comando.find("consultar") != std::string::npos);
}
