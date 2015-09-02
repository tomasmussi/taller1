
#ifndef SENSOR_H

#define SENSOR_H

#include "falla.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct sensor {
	size_t muestras_corrosion;
	size_t contador_corrosion;
	bool hay_ruptura;
} sensor_t;

sensor_t* crear_sensor(size_t umbral_muestras);

void destruir_sensor(sensor_t *sensor);

/**
 * Toma la muestra actual que se esta leyendo del archivo y la registra para ver
 * si hay corrosion o ruptura. Hay que preguntar si el sensor detecto alguna
 * anomalia
 * */
void tomar_medicion(sensor_t *sensor, uint32_t medicion);

/**
 * Informa si el sensor detecto corrosion en algun punto del recorrido.
 * */
bool hay_corrosion(sensor_t *sensor);
void obtener_corrosion(falla_t *corrosion, sensor_t *sensor, size_t medicion,
	double factor);
void limpiar_corrosion(sensor_t *sensor);

bool hay_ruptura(sensor_t *sensor);
void obtener_ruptura(falla_t *ruptura, sensor_t *sensor, size_t medicion,
	double factor);
void limpiar_ruptura(sensor_t *sensor);


#endif //SENSOR_H
