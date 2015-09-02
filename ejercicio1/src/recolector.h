
#ifndef RECOLECTOR_H

#define RECOLECTOR_H

#include <stdint.h>
#include "recorrido.h"
#include "sensor.h"

#define MAX_CARACTERES_ARCHIVO 51

typedef struct recolector {
	char nombre_archivo[MAX_CARACTERES_ARCHIVO];
	sensor_t **sensores;
	uint32_t v_fluido;
	uint32_t v_sensor;
	uint32_t c_sensor;
	size_t mediciones_esperadas;
	size_t recorrido_distancia;
	recorrido_t *recorrido;
} recolector_t;

void crear_recolector(recolector_t *recolector, const char *nombre_archivo, 
		size_t recorrido_distancia, recorrido_t *recorrido);

void destruir_recolector(recolector_t *recolector);

bool procesar_archivo(recolector_t *recolector);

#endif //RECOLECTOR_H