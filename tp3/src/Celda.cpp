#include "Celda.h"

Celda::Celda(const Coordenada& centro, Elemento *elemento)
	: centro(centro), elemento(elemento){
}

const Coordenada Celda::getCoordenada(){
	return centro;
}

void Celda::agregarElemento(Elemento *elemento){
	if (elemento->nivel() > this->elemento->nivel()){
		this->elemento = elemento;
	}
}

char Celda::getCaracter(){
	return this->elemento->caracter();
}
