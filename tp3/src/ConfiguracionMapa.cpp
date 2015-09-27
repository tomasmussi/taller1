
#include "ConfiguracionMapa.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>

ConfiguracionMapa::ConfiguracionMapa() {
}

ConfiguracionMapa::~ConfiguracionMapa() {
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
