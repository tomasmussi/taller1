
#include "sensor.h"

#include <stdio.h>

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

bool tomar_medicion(sensor_t *sensor, uint32_t medicion, size_t numero_muestra){
	if (medicion >= TOPE_CORROSION && medicion <= TOPE_RUPTURA){
		sensor->contador_corrosion++;
		return false;
	} else if (medicion > TOPE_RUPTURA){
		sensor->ultima_falla = crear_falla("RUPTURA", numero_muestra);
		return true;
	} else {
		bool problema = false;
		if (sensor->contador_corrosion >= sensor->muestras_corrosion){
			//printf("Finaliza en numero muestra: %zd habiendo comenzado hace %zd muestras\n", numero_muestra,sensor->contador_corrosion);
			sensor->ultima_falla = crear_falla("CORROSION", numero_muestra - sensor->contador_corrosion);
			problema = true;
		}
		sensor->contador_corrosion = 0;
		return problema;
	}
}

falla_t* obtener_falla(sensor_t *sensor){
	falla_t *falla = sensor->ultima_falla;
	sensor->ultima_falla = NULL;
	return falla;
}
