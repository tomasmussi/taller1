#include "Manzana.h"
#include "Coordenada.h"
#include <list>

Manzana::Manzana(std::list<Coordenada> coordenadas) : Poligono(coordenadas){

}

Manzana::~Manzana() {
}

bool Manzana::superficieEdificada(){
	return false;
}

bool Manzana::superficieArbolada(){
	return false;
}

const char Manzana::caracter(){
	return 'm';
}

size_t Manzana::nivel(){
	return 1;
}
