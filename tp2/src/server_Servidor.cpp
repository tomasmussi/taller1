#include "server_Servidor.h"

Servidor::Servidor(std::string puerto) :proxy(puerto) {

}

Servidor::~Servidor() {
}

void Servidor::iniciar(){
	proxy.start();
	bool seguir = true;
	while(seguir){
		std::string mensajeEntrante;
		getline(std::cin, mensajeEntrante);
		if (mensajeEntrante == "q"){
			seguir = false;
			proxy.finalizar();
		}
	}
	proxy.join();
}
