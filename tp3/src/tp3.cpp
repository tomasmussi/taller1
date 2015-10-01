
#include <iostream>
#include <fstream>
#include <sstream>
#include "ConfiguracionMapa.h"
#include "Mapa.h"

#include "Coordenada.h"
#include "Poligono.h"
#include <list>

void printTest(const char* mensaje, bool assert){
	std::cout << "PRUEBA: " << mensaje << '\t' << ((assert) ? "OK" : "ERROR") << std::endl;
}

void cuadrado(){
	std::list<Coordenada> lista;
	lista.push_back(Coordenada(0,5));
	lista.push_back(Coordenada(5,5));
	lista.push_back(Coordenada(5,0));
	lista.push_back(Coordenada(0,0));
	Poligono p (lista);
	printTest("Tiene 2.5, 2.5", p.tienePunto(Coordenada(2.5,2.5)));
	printTest("Tiene 3, 4", p.tienePunto(Coordenada(3,4)));
	printTest("Tiene 4.99, 4.99", p.tienePunto(Coordenada(4.99,4.99)));
	printTest("Tiene 0.01, 0.01", p.tienePunto(Coordenada(0.01,0.01)));
	printTest("Tiene 0, 0", p.tienePunto(Coordenada(0,0)));

	printTest("No Tiene 2.5, 6", !p.tienePunto(Coordenada(2.5,6)));
	printTest("No Tiene 6, 2.5", !p.tienePunto(Coordenada(6, 2.5)));
	printTest("No Tiene -1, 2.5", !p.tienePunto(Coordenada(-1,2.5)));
	printTest("No Tiene -1, 0", !p.tienePunto(Coordenada(-1,0)));
	printTest("No tiene 10, 10", !p.tienePunto(Coordenada(10,10)));
	printTest("No tiene -4, -4", !p.tienePunto(Coordenada(-4,-4)));
}

void pruebas(){
	cuadrado();
}

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

//	pruebas();
	return 0;
}
