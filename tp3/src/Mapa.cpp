#include "Mapa.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <string>
#include "Coordenada.h"
#include "Elemento.h"
#include "Figura.h"
#include "Poligono.h"
#include "Circulo.h"
#include "Arbol.h"
#include "Agua.h"
#include "Boulevard.h"
#include "Edificio.h"
#include "Semaforo.h"
#include "Manzana.h"

#define LETRA_A 65
#define LETRAS 26

Mapa::Mapa() {
	contEdificiosPublicos = 0;
	areaEdificada = 0;
	areaArbolada = 0;
}

Mapa::~Mapa() {
	for (std::list<Figura*>::iterator it = elementos.begin();
			it != elementos.end(); it++){
		delete (*it);
	}
}

void Mapa::leerObjetos(const char *archivo){
	std::ifstream fileIn(archivo);
	std::string linea;
	while (std::getline(fileIn, linea)){
		std::stringstream ss(linea);
		std::string tipo;
		std::getline(ss, tipo, ',');
		std::string nombreEdificioPublico;
		if (tipo.find("edificio-publico") != std::string::npos){
			std::getline(ss, nombreEdificioPublico, ',');
		}
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
		this->crearElemento(tipo, coordenadas, lat, nombreEdificioPublico);
	}
}

void Mapa::crearElemento(std::string tipo, std::list<Coordenada>& coordenadas,
		std::string radio, std::string nombrePublico){
	Figura *elemento;
	if (tipo == "arbol"){
		std::istringstream iss(radio);
		double radioDouble;
		iss >> radioDouble;
		elemento = new Arbol(*coordenadas.begin(), radioDouble * 1000);
	} else if (tipo == "semaforo"){
		std::istringstream iss(radio);
		double radioDouble;
		iss >> radioDouble;
		elemento = new Semaforo(*coordenadas.begin(), radioDouble * 1000);
	} else if (tipo == "agua"){
		elemento = new Agua(coordenadas);
	} else if (tipo == "boulevard"){
		elemento = new Boulevard(coordenadas);
	} else if (tipo == "manzana"){
		elemento = new Manzana(coordenadas);
	} else if (tipo.find("edificio") != std::string::npos){
		if (tipo == "edificio-privado"){
			elemento = new Edificio(coordenadas);
		} else {
			elemento = new Edificio(coordenadas, nombrePublico,
					LETRA_A + (contEdificiosPublicos++ % LETRAS));
			edificiosPublicos.push_back((Edificio*)elemento);
		}
	}
	if (elemento->superficieEdificada()){
		areaEdificada += elemento->area();
	}
	if (elemento->superficieArbolada()){
		areaArbolada += elemento->area();
	}
	elementos.push_back(elemento);
}

void Mapa::exportarSuperficies(){
	std::cout << "Superficie total edificada: " << (int)(areaEdificada + 0.5)
			<< " metros cuadrados." << std::endl;
	std::cout << "Superficie total arbolada: " << (int)(areaArbolada + 0.5)
			<< " metros cuadrados." <<std::endl;
}

void Mapa::exportarMapa(const ConfiguracionMapa& configuracion){
	std::list<Celda*> celdas = configuracion.getCeldas();
	for (std::list<Celda*>::const_iterator it = celdas.begin();
			it != celdas.end(); it++){
		for (std::list<Figura*>::iterator elemento = elementos.begin();
				elemento != elementos.end(); elemento++){
			if ((*elemento)->tienePunto((*it)->getCoordenada())){
				(*it)->cambiarCaracter((*elemento));
			}
		}
	}
	int cantidad = 0;
	for (std::list<Celda*>::const_iterator it = celdas.begin();
			it != celdas.end(); it++){
		std::cout << (*it)->getCaracter();
		cantidad++;
		if ((cantidad % configuracion.getAncho()) == 0){
			std::cout << std::endl;
		}
	}
}

void Mapa::exportarEdificiosPublicos(){
	for (std::list<Edificio*>::iterator it = edificiosPublicos.begin();
			it != edificiosPublicos.end(); it++){
		std::cout << (*it)->caracter() << ": " << (*it)->getNombre()
				<< std::endl;
	}
}

void Mapa::exportarArchivo(const ConfiguracionMapa& configuracion){
	this->exportarSuperficies();
	this->exportarMapa(configuracion);
	this->exportarEdificiosPublicos();
}
