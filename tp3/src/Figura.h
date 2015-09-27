#ifndef FIGURA_H_
#define FIGURA_H_

#include "Coordenada.h"
#include "Elemento.h"

class Figura : public Elemento {
public:
	Figura();
	virtual ~Figura();
	virtual double area() = 0;
	virtual bool tienePunto(Coordenada punto) = 0;
};

#endif /* FIGURA_H_ */
