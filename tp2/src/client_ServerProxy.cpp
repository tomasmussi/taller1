#include "client_ServerProxy.h"
#include <sstream>

ServerProxy::ServerProxy(std::string ip, std::string puerto) {
	this->socket = new Socket(ip,puerto, 0);
	this->socket->conectar();
}

ServerProxy::~ServerProxy() {
	this->socket->enviar("fin\n");
	delete this->socket;
}

void ServerProxy::informarSeccion(std::string nombreSeccion){
	std::ostringstream builder;
	builder << "conector seccion " << nombreSeccion << std::endl;
	this->socket->enviar(builder.str());
}

void ServerProxy::informarMediciones(unsigned int nivel, unsigned int caudal){
	std::ostringstream builder;
	builder << "actualizar nivel " << nivel << " caudal " << caudal << "\n";
	this->socket->enviar(builder.str());
}

