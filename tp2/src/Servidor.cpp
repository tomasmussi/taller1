#include "Servidor.h"

Servidor::Servidor(std::string puerto) {
	this->proxy = new ClientProxyAceptador(puerto);
}

Servidor::~Servidor() {
	delete this->proxy;
}

void Servidor::iniciar(){
	proxy->start();
	bool seguir = true;
	while(seguir){
		std::string mensajeEntrante;
		getline(std::cin, mensajeEntrante);
		if (mensajeEntrante == "q"){
			seguir = false;
			proxy->finalizar();
		}
	}
	proxy->join();
}
