
#include "recolector.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define BYTES_VELOCIDAD 4
#define BYTES_MEDICION 2
#define SEGUNDOS_EN_MINUTO 60
#define MINUTO_EN_HORAS 60
#define TOLERANCIA_CORROSION_METROS 0.5
#define MASCARA_EOF 0xFFFF

bool procesar_archivo(recolector_t *recolector);

uint32_t parsear_numero(FILE *fp, int bytes);

bool arquitectura_big_endian();

void generar_sensores(recolector_t *recolector);

size_t calcular_mediciones_esperadas(recolector_t *recolector, 
		size_t recorrido_distancia){
	double esperado = (double) recolector->c_sensor * 
			recolector->v_sensor * SEGUNDOS_EN_MINUTO * 
			recorrido_distancia;
	esperado = floor(esperado / recolector->v_fluido);
	return (size_t) esperado;
}

void crear_recolector(recolector_t *recolector, const char *nombre_archivo, 
		size_t recorrido_distancia, recorrido_t *recorrido){
	strncpy(recolector->nombre_archivo, nombre_archivo, MAX_CARACTERES_ARCHIVO);
	recolector->nombre_archivo[MAX_CARACTERES_ARCHIVO - 1] = '\0';
	recolector->recorrido_distancia = recorrido_distancia;
	recolector->recorrido = recorrido;
}

bool procesar_archivo(recolector_t *recolector){
	FILE *fp = fopen(recolector->nombre_archivo, "rb");
	if (fp == NULL){
		fprintf(stderr, "Archivo invalido\n");
		return false;
	}
	recolector->v_fluido = parsear_numero(fp, BYTES_VELOCIDAD);
	recolector->v_sensor = parsear_numero(fp, BYTES_VELOCIDAD);
	recolector->c_sensor = parsear_numero(fp, BYTES_VELOCIDAD);
	recolector->mediciones_esperadas = calcular_mediciones_esperadas(recolector,
			recolector->recorrido_distancia);
	generar_sensores(recolector);
	uint32_t cantidad = 0;
	double factor = (double) recolector->v_fluido;
	factor = factor / (recolector->v_sensor * SEGUNDOS_EN_MINUTO);

	while (! feof(fp)){
		uint32_t medicion = parsear_numero(fp, BYTES_MEDICION);
		if (medicion != MASCARA_EOF){
			size_t n_sens = cantidad % recolector->c_sensor;
			size_t n_muestra = (cantidad / recolector->c_sensor) + 1;
			sensor_t *sensor = recolector->sensores[n_sens];
			tomar_medicion(sensor, medicion, n_muestra);
			falla_t *falla = NULL;
			if (hay_corrosion(sensor)){
				falla = obtener_corrosion(sensor, n_muestra);
				double punto = falla->mediciones * factor;
				double redondeado = punto;
				falla->punto_recorrido = redondeado;
				reportar_falla(recolector->recorrido, falla);
				limpiar_corrosion(sensor);
			}
			if (hay_ruptura(sensor)){
				falla = obtener_ruptura(sensor, n_muestra);
				double punto = falla->mediciones * factor;
				double redondeado = punto;
				falla->punto_recorrido = redondeado;
				reportar_falla(recolector->recorrido, falla);
				limpiar_ruptura(sensor);
			}
			cantidad++;
		}
	}
	if (cantidad != recolector->mediciones_esperadas){
		fprintf(stderr, "Cantidad de muestras incorrectas\n");
	}
	return (fclose(fp) == 0) && (cantidad != recolector->mediciones_esperadas);
}

uint32_t parsear_numero(FILE *fp, int bytes){
	uint32_t numero = 0;
	char *byte = (char*) &numero;
	if (arquitectura_big_endian()){
		for (int i = bytes - 1; i >= 0; i--){
			int c = fgetc(fp);
			*(byte + i) = c;
		}
	} else {
		for (int i = 0; i < bytes; i++){
			*(byte + i) = fgetc(fp);
		}
	}
	return numero;
}

void generar_sensores(recolector_t *recolector){
	recolector->sensores = malloc(recolector->c_sensor * sizeof(sensor_t));
	double umbral = TOLERANCIA_CORROSION_METROS * MINUTO_EN_HORAS * 
			recolector->v_sensor;
	umbral = ceil(umbral / recolector->v_fluido);
	size_t umbral_entero = (size_t) umbral;
	for (int posicion = 0; posicion < recolector->c_sensor; posicion++){
		recolector->sensores[posicion] = crear_sensor(umbral_entero);
	}
}

bool arquitectura_big_endian(){
	int i = 1;
	char *check = (char*) &i;
	return check[0] == 1;
}

void destruir_recolector(recolector_t *recolector){
	for (int posicion = 0; posicion < recolector->c_sensor; posicion++){
		 destruir_sensor(recolector->sensores[posicion]);
	}
	free(recolector->sensores);
}


