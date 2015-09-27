#include "Celda.h"

Celda::Celda(Coordenada centro) {
	this->centro = centro;
	this->caracter = ' ';
}

Celda::~Celda() {
}

const Coordenada Celda::getCoordenada(){
	return centro;
}

void Celda::cambiarCaracter(char caracter){
	this->caracter = caracter;
}

char Celda::getCaracter(){
	return caracter;
}
