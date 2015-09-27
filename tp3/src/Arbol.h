#ifndef ARBOL_H_
#define ARBOL_H_

#include "Circulo.h"
#include "Elemento.h"

class Arbol: public Circulo {
public:
	Arbol(Coordenada centro, double radio);
	~Arbol();
	bool superficieEdificada();
	bool superficieArbolada();
	const char caracter();
};

#endif /* ARBOL_H_ */
