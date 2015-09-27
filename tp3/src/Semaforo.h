#ifndef SEMAFORO_H_
#define SEMAFORO_H_

#include "Circulo.h"
#include "Elemento.h"

class Semaforo: public Circulo {
public:
	Semaforo(Coordenada centro, double radio);
	~Semaforo();
	bool superficieEdificada();
	bool superficieArbolada();
	const char caracter();
};

#endif /* SEMAFORO_H_ */
