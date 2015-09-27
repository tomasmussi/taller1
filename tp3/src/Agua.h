#ifndef AGUA_H_
#define AGUA_H_

#include "Elemento.h"
#include "Poligono.h"

class Agua: public Poligono {
public:
	Agua(std::list<Coordenada> coordenadas);
	~Agua();
	bool superficieEdificada();
	bool superficieArbolada();
	const char caracter();
};

#endif /* AGUA_H_ */
