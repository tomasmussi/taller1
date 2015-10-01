#include "Coordenada.h"
#include <ostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <math.h>

Coordenada::Coordenada(const std::string& latitud,
		const std::string& longitud){
	this->parsearReal(latitud, this->_latitud);
	this->parsearReal(longitud, this->_longitud);
}

Coordenada::Coordenada(double longitud, double latitud){
	this->_longitud = longitud;
	this->_latitud = latitud;
}

void Coordenada::parsearReal(const std::string& cadena, double& numero){
	std::istringstream stream(cadena);
	stream >> numero;
}

double Coordenada::latitud() const {
	return _latitud;
}

double Coordenada::longitud() const {
	return _longitud;
}
