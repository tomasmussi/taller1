
#include "falla.h"

#include <stdio.h>
#include <string.h>

falla_t* crear_falla(const char *tipo, size_t mediciones_atras){
	falla_t *falla = malloc(sizeof(falla_t));
	if (falla == NULL){
		fprintf(stderr, "SIN MEMORIA EN CREAR FALLA\n");
		return NULL;
	}
	strncpy(falla->tipo, tipo, MAX_CARACTERES_TIPO);
	falla->tipo[MAX_CARACTERES_TIPO - 1] = '\0';
	falla->mediciones = mediciones_atras;
	falla->punto_recorrido = 0;
	return falla;
}

void destruir_falla(falla_t *falla){
	free(falla);
}
