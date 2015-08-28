
#ifndef RECOLECTOR_H

#define RECOLECTOR_H

#include <stdint.h>
#include "sensor.h"

#define MAX_CARACTERES_ARCHIVO 51

typedef struct recolector {
	char nombre_archivo[MAX_CARACTERES_ARCHIVO];
	sensor_t **sensores;
	uint32_t velocidad_fluido;
	uint32_t velocidad_sensado;
	uint32_t cantidad_sensores;
} recolector_t;

void crear_recolector(recolector_t *recolector, const char *nombre_archivo);

void destruir_recolector(recolector_t *recolector);



#endif //RECOLECTOR_H
