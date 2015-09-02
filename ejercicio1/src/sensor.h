
#ifndef SENSOR_H

#define SENSOR_H

#include "falla.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct sensor {
	size_t muestras_corrosion;
	size_t contador_corrosion;
	falla_t *falla_corrosion;
	falla_t *falla_ruptura;
} sensor_t;

sensor_t* crear_sensor(size_t umbral_muestras);

void destruir_sensor(sensor_t *sensor);

/**
 * Tomar medicion toma la muestra actual que se esta leyendo del archivo
 * y la registra para ver si hay corrosion o ruptura.
 * Devuelve true si tiene alguna falla que informar.
 * Devuelve false si no tiene nada.
 * */
void tomar_medicion(sensor_t *sensor, uint32_t medicion, size_t numero_muestra);

bool hay_corrosion(sensor_t *sensor);
falla_t* obtener_corrosion(sensor_t *sensor, size_t medicion);
void limpiar_corrosion(sensor_t *sensor);

bool hay_ruptura(sensor_t *sensor);
falla_t* obtener_ruptura(sensor_t *sensor, uint32_t medicion);
void limpiar_ruptura(sensor_t *sensor);


#endif //SENSOR_H
