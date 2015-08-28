
#include "recolector.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define BYTES_VELOCIDAD 4
#define BYTES_MEDICION 2
#define SEGUNDOS_EN_MINUTO 60
#define MASCARA_EOF 0xFFFF

bool procesar_archivo(recolector_t *recolector, const char *nombre_archivo);

uint32_t parsear_numero(FILE *fp, int bytes);

uint16_t parsear_medicion(FILE *fp, int bytes);

bool arquitectura_big_endian();

void generar_sensores(recolector_t *recolector);

void crear_recolector(recolector_t *recolector, const char *nombre_archivo){
	strncpy(recolector->nombre_archivo, nombre_archivo, MAX_CARACTERES_ARCHIVO);
	recolector->nombre_archivo[MAX_CARACTERES_ARCHIVO - 1] = '\0';
	procesar_archivo(recolector, nombre_archivo);
}

bool procesar_archivo(recolector_t *recolector, const char *nombre_archivo){
	FILE *fp = fopen(nombre_archivo, "rb");
	if (fp == NULL){
		fprintf(stderr, "Archivo invalido\n");
		return false;
	}
	recolector->velocidad_fluido = parsear_numero(fp, BYTES_VELOCIDAD);
	recolector->velocidad_sensado = parsear_numero(fp, BYTES_VELOCIDAD);
	recolector->cantidad_sensores = parsear_numero(fp, BYTES_VELOCIDAD);
	generar_sensores(recolector);
	uint32_t cantidad = 0;
	while (! feof(fp)){
		uint32_t medicion = parsear_numero(fp, BYTES_MEDICION);
		if (medicion != MASCARA_EOF){
			if (tomar_medicion(recolector->sensores[cantidad % recolector->cantidad_sensores], medicion)){
				double punto = ((cantidad - 5) * (double)recolector->velocidad_fluido) / (recolector->velocidad_sensado * SEGUNDOS_EN_MINUTO);
				printf("En el punto: %.2f hay algo\n", punto);
			}
			cantidad++;
		}
	}
	printf("Total: %d\n", cantidad);
	return fclose(fp) == 0;
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
	recolector->sensores = malloc(recolector->cantidad_sensores * sizeof(sensor_t));
	for (int posicion = 0; posicion < recolector->cantidad_sensores; posicion++){
		recolector->sensores[posicion] = crear_sensor(4);
	}
}

bool arquitectura_big_endian(){
	int i = 1;
	char *check = (char*) &i;
	return check[0] == 1;
}

void destruir_recolector(recolector_t *recolector){
	for (int posicion = 0; posicion < recolector->cantidad_sensores; posicion++){
		 destruir_sensor(recolector->sensores[posicion]);
	}
	free(recolector->sensores);
}


