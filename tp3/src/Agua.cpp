#include "Agua.h"

Agua::Agua(std::list<Coordenada> coordenadas)
	: Poligono(coordenadas) {
}

Agua::~Agua() {
}

bool Agua::superficieEdificada(){
	return false;
}

bool Agua::superficieArbolada(){
	return false;
}

const char Agua::caracter(){
	return '-';
}

size_t Agua::nivel(){
	return 1;
}
