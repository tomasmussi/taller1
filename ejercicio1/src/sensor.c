
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
	sensor->falla_corrosion = NULL;
	sensor->falla_ruptura = NULL;
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
		sensor->contador_corrosion++;
		sensor->falla_ruptura = crear_falla("RUPTURA", numero_muestra);
		return true;
	} else {
		bool problema = false;
		if (sensor->contador_corrosion >= sensor->muestras_corrosion){
			/*printf("Finaliza en numero muestra: %zd habiendo comenzado
			 hace %zd muestras\n", 
			 numero_muestra,sensor->contador_corrosion);*/
			//size_t origen = numero_muestra - sensor->contador_corrosion;
			//sensor->ultima_falla = crear_falla("CORROSION", origen);
			problema = true;
		}
		sensor->contador_corrosion = 0;
		return problema;
	}
}

bool hay_corrosion(sensor_t *sensor){
	return sensor->contador_corrosion >= sensor->muestras_corrosion;
}

falla_t* obtener_corrosion(sensor_t *sensor, size_t numero_muestra){
	size_t origen = numero_muestra - sensor->contador_corrosion  + 1;
	sensor->falla_corrosion = crear_falla("CORROSION", origen);
	return sensor->falla_corrosion;
}

void limpiar_corrosion(sensor_t *sensor){
	destruir_falla(sensor->falla_corrosion);
	sensor->falla_corrosion = NULL;
	sensor->contador_corrosion = 0;
}

bool hay_ruptura(sensor_t *sensor){
	return sensor->falla_ruptura != NULL;
}

falla_t* obtener_ruptura(sensor_t *sensor, uint32_t medicion){
	return sensor->falla_ruptura;
}

void limpiar_ruptura(sensor_t *sensor){
	destruir_falla(sensor->falla_ruptura);
	sensor->falla_ruptura = NULL;
}

