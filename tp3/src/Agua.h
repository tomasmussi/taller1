#ifndef AGUA_H_
#define AGUA_H_

#include <list>
#include "Elemento.h"
#include "Poligono.h"

class Agua: public Poligono {
public:
	explicit Agua(const std::list<Coordenada>& coordenadas);
	bool superficieEdificada();
	bool superficieArbolada();
	const char caracter();
	size_t nivel();
};

#endif /* AGUA_H_ */
