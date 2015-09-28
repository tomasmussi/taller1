#ifndef MANZANA_H_
#define MANZANA_H_

#include "Elemento.h"
#include "Poligono.h"
#include "Coordenada.h"
#include <list>

class Manzana: public Poligono {
public:
	explicit Manzana(std::list<Coordenada> coordenadas);
	~Manzana();
	bool superficieEdificada();
	bool superficieArbolada();
	const char caracter();
	size_t nivel();
};

#endif /* MANZANA_H_ */
