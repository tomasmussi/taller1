#ifndef SRC_CONECTOR_H_
#define SRC_CONECTOR_H_
#include "Medicion.h"
#include <map>

class Conector {

private:
	int contador;
	int cantidadMuestras;
	std::map<int, int> muestras;
	void calcularModa();

public:
	Conector(int cantidadMuestras);
	void tomarMedicion(Medicion medicion);
	~Conector();

};

#endif /* SRC_CONECTOR_H_ */
