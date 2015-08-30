
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
	double esperado = (double) recolector->cantidad_sensores * 
			recolector->velocidad_sensado * SEGUNDOS_EN_MINUTO * 
			recorrido_distancia;
	esperado = floor(esperado / recolector->velocidad_fluido);
	return (size_t) esperado;
}

void crear_recolector(recolector_t *recolector, const char *nombre_archivo, 
		size_t recorrido_distancia){
	strncpy(recolector->nombre_archivo, nombre_archivo, MAX_CARACTERES_ARCHIVO);
	recolector->nombre_archivo[MAX_CARACTERES_ARCHIVO - 1] = '\0';
	recolector->fallas = cola_crear();
	recolector->recorrido_distancia = recorrido_distancia;
}

bool procesar_archivo(recolector_t *recolector){
	FILE *fp = fopen(recolector->nombre_archivo, "rb");
	if (fp == NULL){
		fprintf(stderr, "Archivo invalido\n");
		return false;
	}
	recolector->velocidad_fluido = parsear_numero(fp, BYTES_VELOCIDAD);
	recolector->velocidad_sensado = parsear_numero(fp, BYTES_VELOCIDAD);
	recolector->cantidad_sensores = parsear_numero(fp, BYTES_VELOCIDAD);
	recolector->mediciones_esperadas = calcular_mediciones_esperadas(recolector,
			recolector->recorrido_distancia);
	generar_sensores(recolector);
	uint32_t cantidad = 0;
	while (! feof(fp)){
		uint32_t medicion = parsear_numero(fp, BYTES_MEDICION);
		if (medicion != MASCARA_EOF){
			/*if (cantidad % recolector->cantidad_sensores == 0){
				printf("Sensor[%d], muestra: %x, medicion numero: %d\n",
				cantidad % recolector->cantidad_sensores, medicion, 
				(cantidad / recolector->cantidad_sensores) + 1);
			}*/
			if (tomar_medicion(recolector->sensores[cantidad % recolector->cantidad_sensores], medicion, (cantidad / recolector->cantidad_sensores) + 1)){
				falla_t *falla = obtener_falla(recolector->sensores[cantidad % recolector->cantidad_sensores]);
				double punto = (falla->mediciones * (double)recolector->velocidad_fluido) / (recolector->velocidad_sensado * SEGUNDOS_EN_MINUTO);
				falla->punto_recorrido = punto;
				/*if (cantidad % recolector->cantidad_sensores == 0){
					printf("Cantidad: %d\n", cantidad);
					printf("Falla mediciones: %zd\n", falla->mediciones);
					printf("Div: %d\n", (cantidad / recolector->cantidad_sensores));
					printf("CUENTA: (%zd  * %d)   /  (%d * %d)\n", 
					(cantidad - falla->mediciones + 1), 
					recolector->velocidad_fluido, recolector->velocidad_sensado,
					SEGUNDOS_EN_MINUTO);
					printf("Punto: %.2f\n", punto);
				}*/
				cola_encolar(recolector->fallas, falla);
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
	recolector->sensores = malloc(recolector->cantidad_sensores * sizeof(sensor_t));
	double umbral = TOLERANCIA_CORROSION_METROS * MINUTO_EN_HORAS * recolector->velocidad_sensado;
	umbral = ceil(umbral / recolector->velocidad_fluido);
	size_t umbral_entero = (size_t) umbral;
	for (int posicion = 0; posicion < recolector->cantidad_sensores; posicion++){
		recolector->sensores[posicion] = crear_sensor(umbral_entero);
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
	cola_destruir(recolector->fallas);
}


