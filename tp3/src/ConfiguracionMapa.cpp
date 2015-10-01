
#include "ConfiguracionMapa.h"
#include "Coordenada.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <list>

ConfiguracionMapa::~ConfiguracionMapa() {
	for (std::list<Celda*>::iterator it = celdas.begin();
			it != celdas.end(); it++){
		delete (*it);
	}
}

bool ConfiguracionMapa::leerArchivo(const char *archivo){
	std::ifstream fileIn(archivo);
	if (!fileIn.is_open()){
		return false;
	}
	std::string linea;
	std::getline(fileIn, linea);
	this->parsearReal(linea, latitudSuperior);
	std::getline(fileIn, linea);
	this->parsearReal(linea, latitudInferior);
	std::getline(fileIn, linea);
	this->parsearReal(linea, longitudIzquierda);
	std::getline(fileIn, linea);
	this->parsearReal(linea, longitudDerecha);
	std::getline(fileIn, linea);
	this->parsearEntero(linea, alto);
	std::getline(fileIn, linea);
	this->parsearEntero(linea, ancho);
	this->crearCeldas();
	return true;
}

void ConfiguracionMapa::parsearReal(std::string cadena, double& numero){
	std::istringstream stream(cadena);
	stream >> numero;
}

void ConfiguracionMapa::parsearEntero(std::string cadena, int& numero){
	std::istringstream stream(cadena);
	stream >> numero;
}

void ConfiguracionMapa::crearCeldas(){
	double incrementoLongitud = (longitudDerecha - longitudIzquierda) / ancho;
	double incrementoLatitud = (latitudSuperior - latitudInferior) / alto;
	for (int alto = this->alto - 1; alto >= 0; alto--){
		double latitudCentro = latitudInferior + incrementoLatitud * alto +
				(incrementoLatitud / 2);
		for (int ancho = 0; ancho < this->ancho; ancho++){
			double longitudCentro = longitudIzquierda +
					incrementoLongitud * ancho + (incrementoLongitud / 2);
			celdas.push_back(new Celda(
					Coordenada(longitudCentro, latitudCentro), &calle));
		}
	}
}

const std::list<Celda*> ConfiguracionMapa::getCeldas() const {
	return celdas;
}

int ConfiguracionMapa::getAncho() const{
	return ancho;
}

