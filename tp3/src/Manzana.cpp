#include "Manzana.h"
#include "Coordenada.h"
#include "Constantes.h"
#include <list>

Manzana::Manzana(const std::list<Coordenada>& coordenadas)
	: Poligono(coordenadas){
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
	return CAPA_DOS;
}
