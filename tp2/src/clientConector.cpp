#include "clientConector.h"
#include <iostream>
#include <map>

Conector::Conector(int cantidadMuestras, ServerProxy *server) {
	this->contador = 0;
	this->cantidadMuestras = cantidadMuestras;
	this->server = server;
}

/* Toma una medicion y la envia al servidor si ya pasaron N cantidad
 * de muestras
 * */
void Conector::tomarMedicion(Medicion medicion){
	nivel[medicion.getNivel()]++;
	caudal[medicion.getCaudal()]++;
	this->contador++;
	if (contador % cantidadMuestras == 0){
		unsigned int nivelInformar = this->calcularModa(nivel);
		unsigned int cauceInformar = this->calcularModa(caudal);
		this->server->informarMediciones(nivelInformar, cauceInformar);
		nivel.clear();
		caudal.clear();
	}
}

unsigned int Conector::calcularModa(std::map<unsigned int,
		unsigned int> muestras){
	// Como las muestras son valores enteros, 0 lo considero el minimo.
	unsigned int moda = 0;
	unsigned int medicionMasAlta = 0;
	for (std::map<unsigned int, unsigned int>::iterator it = muestras.begin();
			it != muestras.end(); it++){
		if (it->second > moda){
			medicionMasAlta = it->first;
			moda = it->second;
		} else if (it->second == moda && it->first > medicionMasAlta){
			medicionMasAlta = it->first;
		}
	}
	return medicionMasAlta;
}

Conector::~Conector() {
}

