#ifndef POLIGONO_H_
#define POLIGONO_H_

#include "Figura.h"
#include "Coordenada.h"
#define GRADO_LONGITUD_EN_METROS 111319
#define GRADO_LATITUD_EN_METROS 111131
#include <list>

class Poligono: public Figura {
private:
	std::list<Coordenada> coordenadas;
public:
	explicit Poligono(std::list<Coordenada> coordenadas);
	~Poligono();
	double area();
	bool tienePunto(Coordenada punto);
	//bool colisionaCon(Figura otraFigura);
};

#endif /* POLIGONO_H_ */
