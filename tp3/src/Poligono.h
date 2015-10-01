#ifndef POLIGONO_H_
#define POLIGONO_H_

#include "Figura.h"
#include "Coordenada.h"
#include "Constantes.h"
#include <list>
#include <vector>

class Poligono: public Figura {
private:
	std::vector<Coordenada> vector;
public:
	explicit Poligono(const std::list<Coordenada>& coordenadas);
	double area();
	bool tienePunto(const Coordenada& punto);
};

#endif /* POLIGONO_H_ */
