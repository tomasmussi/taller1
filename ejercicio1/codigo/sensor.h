
#ifndef SENSOR_H

#define SENSOR_H

#include "falla.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#define TRAMO_INFORME_METROS 5

typedef struct sensor {
	size_t muestras_corrosion;
	size_t contador_corrosion;
	falla_t *ultima_falla;
} sensor_t;

sensor_t* crear_sensor(size_t umbral_muestras);

void destruir_sensor(sensor_t *sensor);

/**
 * Tomar medicion toma la muestra actual que se esta leyendo del archivo
 * y la registra para ver si hay corrosion o ruptura.
 * Devuelve true si tiene alguna falla que informar.
 * Devuelve false si no tiene nada.
 * */
bool tomar_medicion(sensor_t *sensor, uint32_t medicion, size_t numero_muestra);

/**
 * Al haber reportado una falla mediante tomar_medicion, se devuelve
 * dicha falla para que el usuario la reporte como quiera.
 * ADVERTENCIA: ES RESPONSABILIDAD DEL USUARIO DESTRUIR LA FALLA!!!!!!
 * SENSOR NO MANTIENE REGISTRO DE TODAS LAS FALLAS QUE INFORMA
 * */
falla_t* obtener_falla(sensor_t *sensor);

#endif //SENSOR_H
