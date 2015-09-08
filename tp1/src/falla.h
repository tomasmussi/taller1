
#ifndef FALLA_H

#include <stdlib.h>

#define FALLA_H
#define MAX_CARACTERES_TIPO 15

typedef struct falla {
	char tipo[MAX_CARACTERES_TIPO];
	double punto_recorrido;
} falla_t;

/** Crea una falla
 *  PRE: falla apunta a memoria reservada.
 * 	POST: falla creada con su tipo y referencia absoluta de donde esta la falla.
 * */
void crear_falla(falla_t *falla, const char *tipo, double punto_recorrido);

/** Destruye la falla. 
 * PRE: la falla fue creada.
 * */
void destruir_falla(falla_t *falla);

#endif // FALLA_H
