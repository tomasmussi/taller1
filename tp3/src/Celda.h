#ifndef CELDA_H_
#define CELDA_H_
#include "Coordenada.h"
#include "Elemento.h"

class Celda {
private:
	Coordenada centro;
	Elemento *elemento;
public:
	Celda(Coordenada centro, Elemento *elemento);
	~Celda();
	const Coordenada getCoordenada();
	void cambiarCaracter(Elemento *elemento);
	char getCaracter();
};

#endif /* CELDA_H_ */
