
#include "sensor.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define TOPE_CORROSION 0x00A0
#define TOPE_RUPTURA 0x00FF

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


bool tomar_medicion(sensor_t *sensor, uint32_t medicion){
	if (medicion >= TOPE_CORROSION && medicion <= TOPE_RUPTURA){
		sensor->contador_corrosion++;
		return false;
	} else if (medicion > TOPE_RUPTURA){
		printf("RUPTURA\n");
		return true;
	} else {
		bool problema = false;
		if (sensor->contador_corrosion >= sensor->muestras_corrosion){
			printf("CORROSION\n");
			problema = true;
		}
		sensor->contador_corrosion = 0;
		return problema;
	}
}

