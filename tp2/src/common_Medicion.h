#ifndef SRC_MEDICION_H_
#define SRC_MEDICION_H_

#include <string>

/* Representa una medicion de los sensores */
class Medicion {

private:
	int nivel;
	int caudal;

public:
	Medicion(int nivel, int caudal);
	Medicion(std::string pars);
	~Medicion();
	int getNivel();
	int getCaudal();
	bool valida();
};

#endif /* SRC_MEDICION_H_ */
