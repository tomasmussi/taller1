#include "ServerProxy.h"
#include <iostream>

ServerProxy::ServerProxy() {
	// TODO Auto-generated constructor stub

}

ServerProxy::~ServerProxy() {
	// TODO Auto-generated destructor stub
}

void ServerProxy::informarMediciones(unsigned int nivel, unsigned int caudal){
	std::cout << "Nivel " << nivel << " Caudal " << caudal << std::endl;
}

