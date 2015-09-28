#ifndef ELEMENTO_H_
#define ELEMENTO_H_

#include <stdlib.h>

class Elemento {
public:
	Elemento();
	virtual ~Elemento();
	virtual bool superficieEdificada() = 0;
	virtual bool superficieArbolada() = 0;
	virtual const char caracter() = 0;
	virtual size_t nivel() = 0;
};

#endif /* ELEMENTO_H_ */
