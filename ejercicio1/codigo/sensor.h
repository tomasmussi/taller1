
#ifndef SENSOR_H

#define SENSOR_H
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define TRAMO_INFORME_METROS 5

typedef struct sensor {
	size_t muestras_corrosion;
	size_t contador_corrosion;
} sensor_t;

sensor_t* crear_sensor(size_t umbral_muestras);

void destruir_sensor(sensor_t *sensor);

bool tomar_medicion(sensor_t *sensor, uint32_t medicion);

#endif //SENSOR_H
