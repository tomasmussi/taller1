#ifndef ARBOL_H_
#define ARBOL_H_

#include "Circulo.h"
#include "Elemento.h"

class Arbol: public Circulo {
public:
	Arbol(const Coordenada& centro, double radio);
	bool superficieEdificada();
	bool superficieArbolada();
	const char caracter();
	size_t nivel();
};

#endif /* ARBOL_H_ */
