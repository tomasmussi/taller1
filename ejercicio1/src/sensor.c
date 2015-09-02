#include "sensor.h"

#include <stdio.h>

#define TOPE_CORROSION 0x00A0
#define TOPE_RUPTURA 0x00FF

sensor_t* crear_sensor(size_t umbral_muestras, double factor){
	sensor_t *sensor = malloc(sizeof(sensor_t));
	if (sensor == NULL){
		fprintf(stderr, "SIN MEMORIA EN CREAR SENSOR\n");
		return NULL;
	}
	sensor->factor = factor;
	sensor->muestras_corrosion = umbral_muestras;
	sensor->contador_corrosion = 0;
	sensor->hay_ruptura = false;
	return sensor;
}

void destruir_sensor(sensor_t *sensor){
	free(sensor);
}

void tomar_medicion(sensor_t *sensor, uint32_t medicion){
	if (medicion >= TOPE_CORROSION && medicion <= TOPE_RUPTURA){
		sensor->contador_corrosion++;
	} else if (medicion > TOPE_RUPTURA){
		sensor->contador_corrosion++;
		sensor->hay_ruptura = true;
	} else {
		sensor->contador_corrosion = 0;
	}
}

bool hay_corrosion(sensor_t *sensor){
	return sensor->contador_corrosion >= sensor->muestras_corrosion;
}

void obtener_corrosion(falla_t *corrosion, sensor_t *sensor, 
		size_t numero_muestra){
	size_t origen = numero_muestra - sensor->contador_corrosion + 1;
	double punto = origen * sensor->factor;
	crear_falla(corrosion, "CORROSION", punto);
}

void limpiar_corrosion(sensor_t *sensor){
	sensor->contador_corrosion = 0;
}

bool hay_ruptura(sensor_t *sensor){
	return sensor->hay_ruptura;
}

void obtener_ruptura(falla_t *ruptura, sensor_t *sensor, size_t numero_muestra){
	crear_falla(ruptura, "RUPTURA", numero_muestra * sensor->factor);
}

void limpiar_ruptura(sensor_t *sensor){
	sensor->hay_ruptura = false;
}

