#ifndef CIRCULO_H_
#define CIRCULO_H_

#include "Figura.h"
#include "Coordenada.h"

class Circulo: public Figura {
private:
	Coordenada centro;
	double radio;
public:
	Circulo(const Coordenada& centro, double radio);
	double area();
	bool tienePunto(const Coordenada& punto);
};

#endif /* CIRCULO_H_ */
