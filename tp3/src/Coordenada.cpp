#include "Coordenada.h"
#include <ostream>
#include <sstream>
#include <stdlib.h>

Coordenada::Coordenada() {
	latitud = 0;
	longitud = 0;
}

Coordenada::Coordenada(std::string& latitud, std::string& longitud){
	this->parsearReal(latitud, this->latitud);
	this->parsearReal(longitud, this->longitud);
}

Coordenada::Coordenada(double longitud, double latitud){
	this->longitud = longitud;
	this->latitud = latitud;
}

Coordenada::~Coordenada() {
}

void Coordenada::parsearReal(std::string cadena, double& numero){
	std::istringstream stream(cadena);
	stream >> numero;
}

std::ostream& operator<<(std::ostream& os, const Coordenada& obj){
	return os << "(" << obj.latitud << ", " << obj.longitud << ")";
}

double Coordenada::getLatitud(){
	return latitud;
}

double Coordenada::getLongitud(){
	return longitud;
}
