
#ifndef FALLA_H

#include <stdlib.h>

#define FALLA_H
#define MAX_CARACTERES_TIPO 15

typedef struct falla {
	char tipo[MAX_CARACTERES_TIPO];
	double punto_recorrido;
} falla_t;


void crear_falla(falla_t *falla, const char *tipo, double punto_recorrido);

void destruir_falla(falla_t *falla);

#endif // FALLA_H
