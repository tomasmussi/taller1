#ifndef CIRCULO_H_
#define CIRCULO_H_

#include "Figura.h"
#include "Coordenada.h"

class Circulo: public Figura {
private:
	Coordenada centro;
	double radio;
public:
	Circulo(Coordenada centro, double radio);
	~Circulo();
	double area();
	bool tienePunto(Coordenada punto);
	//bool colisionaCon(Figura otraFigura);
};

#endif /* CIRCULO_H_ */
