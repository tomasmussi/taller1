
#include "sensor.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

//#define TOPE_CORROSION 0x00A0
//#define TOPE_RUPTURA 0x00FF
#define TOPE_CORROSION 160
#define TOPE_RUPTURA 255

sensor_t* crear_sensor(size_t umbral_muestras){
	sensor_t *sensor = malloc(sizeof(sensor_t));
	sensor->muestras_corrosion = umbral_muestras;
	sensor->contador_corrosion = 0;
	if (sensor == NULL){
		fprintf(stderr, "SIN MEMORIA EN CREAR SENSOR\n");
		return NULL;
	}
	return sensor;
}

void destruir_sensor(sensor_t *sensor){
	free(sensor);
}


void tomar_medicion(sensor_t *sensor, uint32_t medicion){
	if (medicion >= TOPE_CORROSION){
		sensor->contador_corrosion++;
	} else if (medicion > TOPE_RUPTURA){
		printf("RUPTURA\n");
	} else {
		if (sensor->contador_corrosion >= sensor->muestras_corrosion){
			printf("CORROSION\n");
		}
		sensor->contador_corrosion = 0;
	}
}

