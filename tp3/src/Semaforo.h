#ifndef SEMAFORO_H_
#define SEMAFORO_H_

#include "Circulo.h"
#include "Elemento.h"

class Semaforo: public Circulo {
public:
	Semaforo(Coordenada centro, double radio);
	bool superficieEdificada();
	bool superficieArbolada();
	const char caracter();
	size_t nivel();
};

#endif /* SEMAFORO_H_ */
