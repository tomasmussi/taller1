#ifndef CELDA_H_
#define CELDA_H_
#include "Coordenada.h"

class Celda {
private:
	Coordenada centro;
	char caracter;
public:
	Celda(Coordenada centro, char caracter);
	~Celda();
};

#endif /* CELDA_H_ */
