#include "Boulevard.h"
#include "Coordenada.h"
#include <list>

Boulevard::Boulevard(std::list<Coordenada> coordenadas)
	: Poligono(coordenadas) {
}

Boulevard::~Boulevard() {
}

bool Boulevard::superficieEdificada(){
	return false;
}

bool Boulevard::superficieArbolada(){
	return false;
}

const char Boulevard::caracter(){
	return 'b';
}

size_t Boulevard::nivel(){
	return 2;
}
