
#include <iostream>
#include <fstream>
#include <sstream>
#include "ConfiguracionMapa.h"
#include "Mapa.h"

void leerObjetos(const char *archivo){}

int main() {
	ConfiguracionMapa configMapa;
	configMapa.leerArchivo("/home/tomas/repos/taller1/tp3/tests/test1/configuracion.txt");
	Mapa mapa;
	mapa.leerObjetos("/home/tomas/repos/taller1/tp3/tests/test1/mapa.txt");

	return 0;
}
