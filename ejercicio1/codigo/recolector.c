
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


	//printf("CUENTA: (%d)   /  (%d * %d)\n", recolector->v_fluido, recolector->v_sensor, SEGUNDOS_EN_MINUTO);
	//int count = 0;

	//printf("Cantidad de sensores: %d\n", recolector->c_sensor);

	while (! feof(fp)){
		uint32_t medicion = parsear_numero(fp, BYTES_MEDICION);
		if (medicion != MASCARA_EOF){
			/*if (cantidad % recolector->c_sensor == 0){
				printf("Sensor[%d], muestra: %x, medicion numero: %d\n",
				cantidad % recolector->c_sensor, medicion, 
				(cantidad / recolector->c_sensor) + 1);
			}*/
			size_t n_sens = cantidad % recolector->c_sensor;
			size_t n_muestra = (cantidad / recolector->c_sensor) + 1;
			if (n_sens == 5){
				printf("%zd,%d\n", n_muestra, medicion);
			}
			if (tomar_medicion(recolector->sensores[n_sens], medicion, n_muestra)){
				falla_t *falla = obtener_falla(recolector->sensores[n_sens]);
				//count++;
				

				double punto = falla->mediciones * factor;
				double redondeado = punto;
				falla->punto_recorrido = redondeado;

				/*char num[200];
				sprintf(num, "%.2f",punto);
				if (strcmp(num, "4.43") == 0){
					printf("Medicion %zd del sensor %zd\n",n_muestra , n_sens);
				}*/


				/*char num[200];
				sprintf(num, "%.2f",punto);
				//if (count == 22){
				if (strcmp(num, "303.89") == 0){
					printf("Medicion %zd del sensor %zd\n",n_muestra , n_sens);
					printf("Sensor numero: %zd\n", n_sens);
					printf("Cantidad: %d\n", cantidad);
					printf("Falla mediciones: %zd\n", falla->mediciones);
					printf("Div: %d\n", (cantidad / recolector->c_sensor));
					printf("CUENTA: (%zd  * %d)   /  (%d * %d)\n", 
					(falla->mediciones), 
					recolector->v_fluido, recolector->v_sensor,
					SEGUNDOS_EN_MINUTO);
					printf("Punto: %.2f\n", punto);
					exit(1);
				}
				reportar_falla(recolector->recorrido, falla);*/
				destruir_falla(falla);
			}
			cantidad++;
		}
	}

	size_t n_sens = cantidad % recolector->c_sensor;
	size_t n_muestra = (cantidad / recolector->c_sensor) + 1;
	uint32_t medicion = 0;
	for (int posicion = 0; posicion < recolector->c_sensor; posicion++){
		if (tomar_medicion(recolector->sensores[n_sens], medicion, n_muestra)){
			falla_t *falla = obtener_falla(recolector->sensores[n_sens]);
			double punto = falla->mediciones * factor;
			double redondeado = punto;
			falla->punto_recorrido = redondeado;
			reportar_falla(recolector->recorrido, falla);
			destruir_falla(falla);
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


