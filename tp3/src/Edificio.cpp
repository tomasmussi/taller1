#include "Edificio.h"
#include <iostream>

Edificio::Edificio(std::list<Coordenada> coordenadas)
	: Poligono(coordenadas) {
	caracterInterno = 'e';
	nombre = "";
}

Edificio::Edificio(std::list<Coordenada> coordenadas, std::string nombre,
	char caracter) : Poligono(coordenadas){
	caracterInterno = caracter;
	this->nombre = nombre;
}

Edificio::~Edificio() {
}

bool Edificio::superficieEdificada(){
	return true;
}

bool Edificio::superficieArbolada(){
	return false;
}

const char Edificio::caracter(){
	return caracterInterno;
}

const std::string Edificio::getNombre(){
	return nombre;
}
