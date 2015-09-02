#ifndef SENSOR_H

#define SENSOR_H

#include "falla.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

/** Estructura del sensor */
typedef struct sensor {
	size_t muestras_corrosion;
	size_t contador_corrosion;
	double factor;
	bool hay_ruptura;
} sensor_t;

/** 
 * Crea un sensor con el umbral de muestras para detectar corrosion y
 * con el factor que hay que usar para obtener el punto total del recorrido
 * a partir de un numero de muestra.
 * */
sensor_t* crear_sensor(size_t umbral_muestras, double factor);

/** Destruye el sensor */
void destruir_sensor(sensor_t *sensor);

/**
 * Toma la muestra actual que se esta leyendo del archivo y la registra para ver
 * si hay corrosion o ruptura. Hay que preguntar si el sensor detecto alguna
 * anomalia.
 * */
void tomar_medicion(sensor_t *sensor, uint32_t medicion);

/** Informa si el sensor detecto corrosion. */
bool hay_corrosion(sensor_t *sensor);

/** Si hay corrosion, obtiene informacion de la falla. */
void obtener_corrosion(falla_t *corrosion, sensor_t *sensor, size_t medicion);
	
/** Luego de haber obtenido la falla, hay que resetear la cuenta del sensor. */
void limpiar_corrosion(sensor_t *sensor);

/** Informa si el sensor detecto ruptura. */
bool hay_ruptura(sensor_t *sensor);
 
/** Si hubo ruptura, obtener la informacion de la falla. */
void obtener_ruptura(falla_t *ruptura, sensor_t *sensor, size_t medicion);

/** Limpia el indicador de ruptura del sensor. */
void limpiar_ruptura(sensor_t *sensor);


#endif //SENSOR_H
