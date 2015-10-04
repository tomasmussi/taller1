#ifndef CELDA_H_
#define CELDA_H_
#include "Coordenada.h"
#include "Elemento.h"

/* Representa una celda del mapa a exportar */
class Celda {
private:
	Coordenada centro;
	Elemento *elemento;
public:
	Celda(const Coordenada& centro, Elemento *elemento);
	const Coordenada& getCoordenada();
	/* Agrega un elemento que esta contenido en esta celda. */
	void agregarElemento(Elemento *elemento);
	/* Caracter con el cual pintar la celda en la exportacion. */
	char getCaracter();
};

#endif /* CELDA_H_ */
