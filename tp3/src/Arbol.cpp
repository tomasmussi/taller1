#include "Arbol.h"
#include "Coordenada.h"
#include "Constantes.h"

Arbol::Arbol(const Coordenada& centro, double radio)
	: Circulo(centro, radio) {
}

bool Arbol::superficieEdificada(){
	return false;
}

bool Arbol::superficieArbolada(){
	return true;
}

const char Arbol::caracter(){
	return '@';
}

size_t Arbol::nivel(){
	return CAPA_TRES;
}
