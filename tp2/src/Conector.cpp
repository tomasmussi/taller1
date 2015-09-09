#include "Conector.h"
#include <iostream>

Conector::Conector(int cantidadMuestras) {
	this->contador = 0;
	this->cantidadMuestras = cantidadMuestras;
}

void Conector::tomarMedicion(Medicion medicion){
	muestras[medicion.getCauce()]++;
	this->contador++;
	if (this->contador % this->cantidadMuestras == 0){
		this->calcularModa();
		this->muestras.clear();
	}
}

void Conector::calcularModa(){
	// Asumo que las mediciones de cauce empiezan desde 1 por lo que el 0 es minimo
	int moda = 0;
	int valorMasAlto = 0;
	for (std::map<int, int>::iterator it = this->muestras.begin(); it != this->muestras.end(); it++){
		if (it->second > moda){
			valorMasAlto = it->first;
			moda = it->second;
		} else if (it->second == moda && it->first > valorMasAlto){
			valorMasAlto = it->first;
		}
	}
	std::cout << "Moda: " << moda << ". Cauce: " << valorMasAlto << std::endl;
}

Conector::~Conector() {
}

