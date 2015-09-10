
#include <iostream>
#include <stdlib.h>
#include <sstream>

#include "Conector.h"
#include "Socket.h"

using namespace std;
#define ARGUMENTOS_CONECTOR 5

int main(int argc, char *argv[]) {
	if (argc != ARGUMENTOS_CONECTOR){
		cout << "Cantidad invalida de argumentos\nEjemplo\n";
		cout << "./tp 127.0.0.1 3333 seccion1 100\n";
		return 1;
	}
	std::string ip = argv[1];
	std::string puerto = argv[2];
	std::string nombreSeccion = argv[3];
	//int cantidadMuestras = atoi(argv[4]);

	Socket socket(ip, puerto);
	socket.conectar();
	socket.enviar("Hola mundo :D:D:D");

	/*std::string str = "";
	Conector conector(cantidadMuestras);
	while(getline(cin, str)) {
		Medicion medicion(str);
		conector.tomarMedicion(medicion);
	}*/
	return 0;
}
