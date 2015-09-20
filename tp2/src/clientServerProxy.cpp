#include "clientServerProxy.h"
#include <sstream>
#include <string>

ServerProxy::ServerProxy(std::string ip, std::string puerto)
	: socket(ip, puerto, 0) {
	this->socket.conectar();
}

ServerProxy::~ServerProxy() {
}

/* Envia al servidor la seccion de la cual se enviaran actualizaciones */
void ServerProxy::informarSeccion(std::string nombreSeccion){
	std::ostringstream builder;
	builder << "conector seccion " << nombreSeccion << std::endl;
	this->socket.enviar(builder.str());
}

/* Envia al servidor las modas de una cantidad de mediciones */
void ServerProxy::informarMediciones(unsigned int nivel, unsigned int caudal){
	std::ostringstream builder;
	builder << "actualizar nivel " << nivel << " caudal " << caudal << "\n";
	this->socket.enviar(builder.str());
}

/* Avisa que termina y cierra la conexion */
void ServerProxy::finalizar(){
	this->socket.enviar("fin\n");
	this->socket.cerrar();
}

