#ifndef CELDA_H_
#define CELDA_H_
#include "Coordenada.h"
#include "Elemento.h"

class Celda {
private:
	Coordenada centro;
	Elemento *elemento;
public:
	Celda(const Coordenada& centro, Elemento *elemento);
	const Coordenada getCoordenada();
	void cambiarElemento(Elemento *elemento);
	char getCaracter();
};

#endif /* CELDA_H_ */
