#include <iostream>
#include <stdlib.h>
#include <sstream>

#include "server_Servidor.h"

#define ARGUMENTOS_SERVIDOR 2

int main(int argc, char *argv[]) {
	if (argc !=ARGUMENTOS_SERVIDOR){
		std::cout << "INVALIDO\n";
		return 1;
	}
	std::string puerto = std::string(argv[1]);
	Servidor servidor(puerto);
	servidor.iniciar();
	return 0;
}
