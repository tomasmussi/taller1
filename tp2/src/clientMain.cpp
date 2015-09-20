#include "clientConector.h"
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>

#define ARGUMENTOS_CONECTOR 5
#define ARGUMENTOS_SERVIDOR 2

int main(int argc, char *argv[]) {
	if (argc != ARGUMENTOS_CONECTOR){
		std::cout << "INVALIDO\n";
		return 1;
	}
	std::string ip(argv[1]);
	std::string puerto(argv[2]);
	std::string nombreSeccion(argv[3]);
	int cantidadMuestras = atoi(argv[4]);

	ServerProxy server(ip, puerto);
	server.informarSeccion(nombreSeccion);

	std::string str = "";
	Conector conector(cantidadMuestras, &server);
	while(std::getline(std::cin, str)) {
		Medicion medicion(str);
		if (medicion.valida()){
			conector.tomarMedicion(medicion);
		}
	}
	server.finalizar();
	return 0;
}
