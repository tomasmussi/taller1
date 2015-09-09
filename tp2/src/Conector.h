#ifndef SRC_CONECTOR_H_
#define SRC_CONECTOR_H_
#include "Medicion.h"
#include "ServerProxy.h"
#include <map>

class Conector {

private:
	int contador;
	int cantidadMuestras;
	ServerProxy server;
	std::map<unsigned int, unsigned int> nivel;
	std::map<unsigned int, unsigned int> caudal;
	unsigned int calcularModa(std::map<unsigned int, unsigned int> muestras);

public:
	Conector(int cantidadMuestras);
	void tomarMedicion(Medicion medicion);
	~Conector();

};

#endif /* SRC_CONECTOR_H_ */
