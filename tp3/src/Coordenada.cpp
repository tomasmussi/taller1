#include "Coordenada.h"
#include <ostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <math.h>

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

double Coordenada::getLatitud() const{
	return latitud;
}

double Coordenada::getLongitud() const{
	return longitud;
}

double Coordenada::distanciaCon(const Coordenada& otroPunto) const{
	double latitudCuadrado = pow(latitud - otroPunto.latitud, 2);
	double longitudCuadrado = pow(longitud - otroPunto.longitud, 2);
	return sqrt(latitudCuadrado + longitudCuadrado);
}

bool Coordenada::operator ==(const Coordenada& otro) const{
	return longitud == otro.longitud && latitud == otro.latitud;
}
