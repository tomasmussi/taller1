#ifndef AGUA_H_
#define AGUA_H_

#include <list>
#include "Elemento.h"
#include "Poligono.h"

class Agua: public Poligono {
public:
	explicit Agua(std::list<Coordenada> coordenadas);
	~Agua();
	bool superficieEdificada();
	bool superficieArbolada();
	const char caracter();
	size_t nivel();
};

#endif /* AGUA_H_ */
