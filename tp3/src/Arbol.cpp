#include "Arbol.h"
#include "Coordenada.h"

Arbol::Arbol(Coordenada centro, double radio) : Circulo(centro, radio) {
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
	return 3;
}
