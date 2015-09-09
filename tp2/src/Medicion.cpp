#include "Medicion.h"
#include <iostream>
#include <string>
#include <sstream>

Medicion::Medicion(std::string pars) {
	this->nivel = 0;
	this->cauce = 0;
	std::istringstream ss(pars);
	std::string uno;
	ss >> uno;
	ss >> this->nivel;
	ss >> uno;
	ss >> this->cauce;
	//std::cout << "nivel: " << this->nivel << "\t\tCauce: " << this->cauce << std::endl;
}

Medicion::~Medicion() {
}

int Medicion::getCauce(){
	return this->cauce;
}
