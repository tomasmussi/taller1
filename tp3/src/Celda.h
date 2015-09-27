#ifndef CELDA_H_
#define CELDA_H_
#include "Coordenada.h"

class Celda {
private:
	Coordenada centro;
	char caracter;
public:
	explicit Celda(Coordenada centro);
	~Celda();
	const Coordenada getCoordenada();
	void cambiarCaracter(char caracter);
	char getCaracter();
};

#endif /* CELDA_H_ */
