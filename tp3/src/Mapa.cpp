#include "Mapa.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include "Coordenada.h"
#include "Poligono.h"
#include "Circulo.h"

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
	std::cout << "Tipo: " << tipo << std::endl;
	for (std::list<Coordenada>::iterator it = coordenadas.begin(); it != coordenadas.end(); it++){
		std::cout << "Coord: " << *it << "\n";
	}
	if (tipo == "arbol" || tipo == "semaforo"){
		std::istringstream iss(radio);
		double radioDouble;
		iss >> radioDouble;
		Circulo circulo(*coordenadas.begin(), radioDouble * 1000);
		std::cout << "AREA DEL CIRCULO: " << circulo.area() << std::endl;
	} else {
		Poligono figura(coordenadas);
		std::cout << "AREA DEL POLIGONO: " << figura.area() << std::endl;
	}
}
