
#include "ConfiguracionMapa.h"
#include "Coordenada.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>

ConfiguracionMapa::ConfiguracionMapa() {
}

ConfiguracionMapa::~ConfiguracionMapa() {
	for (std::list<Celda*>::iterator it = celdas.begin(); it != celdas.end(); it++){
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

	// TODO: Sacar cuando tenga el tp
	std::cout << std::setprecision(10);
	std::cout << latitudSuperior << "\n" << latitudInferior << '\n' << longitudIzquierda << '\n'
			<< longitudDerecha << '\n' << alto << '\n' << ancho << '\n';
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
	double limiteAnteriorLatitud = latitudSuperior;
	while (limiteAnteriorLatitud > latitudInferior){
		double limiteAnteriorLongitud = longitudIzquierda;
		double latitudCentro = limiteAnteriorLatitud - (incrementoLatitud / 2);
		while (limiteAnteriorLongitud < longitudDerecha){
			double longitudCentro = limiteAnteriorLongitud + (incrementoLongitud / 2);
			std::cout << "Coord: " << Coordenada(longitudCentro, latitudCentro) << std::endl;
			Celda *celda = new Celda(Coordenada(longitudCentro, latitudCentro));
			celdas.push_back(celda);
			limiteAnteriorLongitud += incrementoLongitud;
		}
		limiteAnteriorLatitud -= incrementoLatitud;
	}
}

const std::list<Celda*> ConfiguracionMapa::getCeldas() const {
	return celdas;
}

int ConfiguracionMapa::getAncho() const{
	return ancho;
}

