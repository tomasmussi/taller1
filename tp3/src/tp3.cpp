
#include <iostream>
#include <fstream>
#include <sstream>
#include "ConfiguracionMapa.h"
#include "Mapa.h"

void leerObjetos(const char *archivo){}

int main(int argc, char* argv[]) {
	if (argc != 3){
		std::cerr << "Cantidad invalida de archivos" << std::endl;
		return 1;
	}
	ConfiguracionMapa configMapa;
	configMapa.leerArchivo(argv[1]);
	Mapa mapa;
	mapa.leerObjetos(argv[2]);
	mapa.exportarArchivo(configMapa);
	return 0;
}
