#include "Boulevard.h"
#include "Coordenada.h"
#include "Constantes.h"
#include <list>

Boulevard::Boulevard(std::list<Coordenada> coordenadas)
	: Poligono(coordenadas) {
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
	return CAPA_DOS;
}
