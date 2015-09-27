#ifndef MANZANA_H_
#define MANZANA_H_

#include "Elemento.h"
#include "Poligono.h"
#include "Coordenada.h"
#include <list>

class Manzana: public Poligono {
public:
	Manzana(std::list<Coordenada> coordenadas);
	~Manzana();
	bool superficieEdificada();
	bool superficieArbolada();
	const char caracter();
};

#endif /* MANZANA_H_ */
