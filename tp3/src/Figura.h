#ifndef FIGURA_H_
#define FIGURA_H_

#include "Coordenada.h"
#include "Elemento.h"

class Figura : public Elemento {
public:
	virtual ~Figura();
	/* Calculo del area de una figura. */
	virtual double area() = 0;
	/* Informa si el punto esta contenido en la figura. */
	virtual bool tienePunto(const Coordenada& punto) = 0;
};

#endif /* FIGURA_H_ */
