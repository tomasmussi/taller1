
#include "falla.h"

#include <stdio.h>
#include <string.h>

void crear_falla(falla_t *falla, const char *tipo, double punto_recorrido){
	strncpy(falla->tipo, tipo, MAX_CARACTERES_TIPO);
	falla->tipo[MAX_CARACTERES_TIPO - 1] = '\0';
	falla->punto_recorrido = punto_recorrido;
}

void destruir_falla(falla_t *falla){
}
