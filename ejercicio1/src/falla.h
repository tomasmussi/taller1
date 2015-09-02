
#ifndef FALLA_H

#include <stdlib.h>

#define FALLA_H
#define MAX_CARACTERES_TIPO 15

typedef struct falla {
	char tipo[MAX_CARACTERES_TIPO];
	size_t mediciones;
	double punto_recorrido;
} falla_t;


falla_t* crear_falla(const char *tipo, size_t mediciones_atras);

void destruir_falla(falla_t *falla);

#endif // FALLA_H
