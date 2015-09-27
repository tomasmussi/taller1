#include "Semaforo.h"

Semaforo::Semaforo(Coordenada centro, double radio) : Circulo(centro, radio) {
}

Semaforo::~Semaforo() {
}

bool Semaforo::superficieEdificada(){
	return false;
}

bool Semaforo::superficieArbolada(){
	return false;
}

const char Semaforo::caracter(){
	return '#';
}

