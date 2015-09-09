
#include <iostream>
#include <stdlib.h>
#include <sstream>

#include "Conector.h"

using namespace std;
#define ARGUMENTOS_CONECTOR 5

int main(int argc, char *argv[]) {
	if (argc != ARGUMENTOS_CONECTOR){
		cout << "Cantidad invalida de argumentos\nEjemplo\n";
		cout << "./tp 127.0.0.1 6452 seccion1 100\n";
		return 1;
	}
	std::string ip = argv[1];
	std::string puerto = argv[2];
	std::string nombreSeccion = argv[3];
	int cantidadMuestras = atoi(argv[4]);

	std::string str = "";
	Conector conector(cantidadMuestras);
	bool continuar = getline(cin, str);
	while(continuar) {
		int contador = 0;
		while (continuar && contador < cantidadMuestras){
			istringstream ss(str);
			std::string uno;
			while (ss >> uno){
				cout << uno << endl;
			}
			continuar = getline(cin, str);
			contador++;
		}
		cout << "pasa\n";
	}
	return 0;
}
