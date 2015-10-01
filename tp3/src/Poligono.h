#ifndef POLIGONO_H_
#define POLIGONO_H_

#include "Figura.h"
#include "Coordenada.h"
#include "Constantes.h"
#include <list>

class Poligono: public Figura {
private:
	std::list<Coordenada> coordenadas;
	Coordenada v_sub(Coordenada a, Coordenada b);
	int getSide(Coordenada a, Coordenada b);
	double producto(Coordenada a, Coordenada b);
public:
	explicit Poligono(const std::list<Coordenada>& coordenadas);
	double area();
	bool tienePunto(const Coordenada& punto);
};

#endif /* POLIGONO_H_ */
