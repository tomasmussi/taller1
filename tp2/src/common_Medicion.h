#ifndef SRC_MEDICION_H_
#define SRC_MEDICION_H_

#include <string>

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
};

#endif /* SRC_MEDICION_H_ */
