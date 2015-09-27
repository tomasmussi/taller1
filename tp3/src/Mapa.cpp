#include "Mapa.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include "Coordenada.h"
#include "Elemento.h"
#include "Poligono.h"
#include "Circulo.h"
#include "Arbol.h"
#include "Agua.h"
#include "Boulevard.h"
#include "Edificio.h"
#include "Semaforo.h"
#include "Manzana.h"

Mapa::Mapa() {
}

Mapa::~Mapa() {
}

void Mapa::leerObjetos(const char *archivo){
	std::ifstream fileIn(archivo);
	std::string linea;
	while (std::getline(fileIn, linea)){
		std::stringstream ss(linea);
		std::string tipo;
		std::getline(ss, tipo, ',');
		std::list<Coordenada> coordenadas;

		std::string lat;
		std::string lon;
		std::getline(ss, lat, ',');
		bool continuar = std::getline(ss, lon, ',') != NULL;
		Coordenada coord(lat, lon);
		coordenadas.push_back(coord);

		while (continuar) {
			continuar &= std::getline(ss, lat, ',') != NULL;
			bool par = std::getline(ss, lon, ',') != NULL;
			if (continuar){
				if (par){
					Coordenada coord(lat, lon);
					coordenadas.push_back(coord);
				}
			}
		}
		this->crearElemento(tipo, coordenadas, lat);
	}
}

void Mapa::crearElemento(std::string tipo, std::list<Coordenada>& coordenadas,
		std::string radio){

	//std::cout << "AREA DEL POLIGONO: " << figura.area() << std::endl;

	std::cout << "Tipo: " << tipo << std::endl;
	for (std::list<Coordenada>::iterator it = coordenadas.begin(); it != coordenadas.end(); it++){
		std::cout << "Coord: " << *it << "\n";
	}
	if (tipo == "arbol"){
		std::istringstream iss(radio);
		double radioDouble;
		iss >> radioDouble;
		Arbol arbol(*coordenadas.begin(), radioDouble * 1000);
		std::cout << "AREA DEL arbol: " << arbol.area() << std::endl;
	} else if (tipo == "semaforo"){
		std::istringstream iss(radio);
		double radioDouble;
		iss >> radioDouble;
		Arbol arbol(*coordenadas.begin(), radioDouble * 1000);
		std::cout << "AREA DEL semaforo: " << arbol.area() << std::endl;
	} else {
		/*Poligono pol(coordenadas);
		std::cout << "AREA DEL POLIGONO: " << pol.area() << std::endl;*/
	}

	/*else if (tipo == "agua"){
		Figura agua = Agua(coordenadas);
	} else if (tipo == "boulevard"){

	} else if (tipo == "manzana"){

	} else if (tipo.find("edificio") != std::string::npos){
		if ("edificio-privado"){

		} else {

		}
	}*/
}
