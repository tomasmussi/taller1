#include "Semaforo.h"
#include "Constantes.h"

Semaforo::Semaforo(const Coordenada& centro, double radio)
	: Circulo(centro, radio) {
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

size_t Semaforo::nivel(){
	return CAPA_TRES;
}
