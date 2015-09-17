#include "server_MensajeConector.h"

MensajeConector::MensajeConector(std::string mensaje) {
	std::stringstream ss(mensaje);
	std::string item;
	std::getline(ss, item, '\n');
	this->parsearSeccion(item);
	std::getline(ss, item, '\n');
	while (item != "fin"){
		std::stringstream parcial(item);
		std::string medicion;
		int nivel, caudal;
		parcial >> medicion; // actualizar
		parcial >> medicion; // nivel
		parcial >> nivel; // numero
		parcial >> medicion; // caudal
		parcial >> caudal;
		mediciones.push_back(new Medicion(nivel,caudal));
		std::getline(ss, item, '\n');
	}
	iterador = mediciones.begin();
}

void MensajeConector::parsearSeccion(std::string mensaje){
	std::stringstream ss(mensaje);
	std::string seccion;
	ss >> seccion;
	ss >> seccion;
	ss >> seccion;
	this->seccion = seccion;
}

MensajeConector::~MensajeConector() {
}

std::string MensajeConector::getSeccion(){
	return seccion;
}

bool MensajeConector::hayActualizacion(){
	return iterador != mediciones.end();
}

Medicion* MensajeConector::getMedicionActual(){
	return *iterador;
}

void MensajeConector::avanzarMedicion(){
	iterador++;
}



