#include "Medicion.h"
#include <iostream>
#include <string>
#include <sstream>

Medicion::Medicion(std::string pars) {
	this->nivel = 0;
	this->caudal = 0;
	std::istringstream stream(pars);
	std::string valor;
	stream >> valor;
	stream >> this->nivel;
	stream >> valor;
	stream >> this->caudal;
}

Medicion::~Medicion() {
}

int Medicion::getNivel(){
	return this->nivel;
}

int Medicion::getCaudal(){
	return this->caudal;
}
