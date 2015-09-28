#include "Celda.h"

Celda::Celda(Coordenada centro, Elemento *elemento) {
	this->centro = centro;
	this->elemento = elemento;
}

Celda::~Celda() {
}

const Coordenada Celda::getCoordenada(){
	return centro;
}

void Celda::cambiarCaracter(Elemento *elemento){
	if (elemento->nivel() > this->elemento->nivel()){
		this->elemento = elemento;
	}
}

char Celda::getCaracter(){
	return this->elemento->caracter();
}
