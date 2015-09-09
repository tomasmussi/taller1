#ifndef SRC_MEDICION_H_
#define SRC_MEDICION_H_

#include <string>

class Medicion {

private:
	int nivel;
	int cauce;

public:
	Medicion(std::string pars);
	~Medicion();
	int getCauce();
};

#endif /* SRC_MEDICION_H_ */
