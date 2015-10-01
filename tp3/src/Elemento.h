#ifndef ELEMENTO_H_
#define ELEMENTO_H_

#include <stdlib.h>
#include <list>
#include <string>

class Elemento {
public:
	virtual ~Elemento();
	/* Informa si hay que incluir el area del elemento para el
	 * calculo de superficie edificada. */
	virtual bool superficieEdificada() = 0;
	/* Informa si hay que incluir el area del elemento para el
	 * calculo de superficie arbolada. */
	virtual bool superficieArbolada() = 0;
	/* Devuelve el caracter representativo del elemento del mapa. */
	virtual const char caracter() = 0;
	/* Devuelve el nivel o capa a la cual pertenece el elemento.
	 * Si hay dos elementos de capas distintas, predomina el elemento
	 * de capa mas alta
	 * */
	virtual size_t nivel() = 0;
};

#endif /* ELEMENTO_H_ */
