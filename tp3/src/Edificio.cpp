#include "Edificio.h"
#include "Constantes.h"
#include <string>
#include <list>

Edificio::Edificio(const std::list<Coordenada>& coordenadas)
	: Poligono(coordenadas) {
	caracterInterno = 'e';
	nombre = "";
}

Edificio::Edificio(const std::list<Coordenada>& coordenadas,
		const std::string& nombre, const char caracter)
	: Poligono(coordenadas){
	caracterInterno = caracter;
	this->nombre = nombre;
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

size_t Edificio::nivel(){
	return caracterInterno == 'e' ? CAPA_CUATRO : CAPA_TRES;
}
