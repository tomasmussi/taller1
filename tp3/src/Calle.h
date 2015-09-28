#ifndef SRC_CALLE_H_
#define SRC_CALLE_H_

#include "Elemento.h"

class Calle: public Elemento {
public:
	Calle();
	~Calle();
	bool superficieEdificada();
	bool superficieArbolada();
	const char caracter();
	size_t nivel();
};

#endif /* SRC_CALLE_H_ */
