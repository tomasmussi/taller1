

#include "recorrido.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool leer_archivo(recorrido_t *recorrido);

void crear_recorrido(recorrido_t *recorrido, const char *nombre_archivo){
	strncpy(recorrido->nombre_archivo, nombre_archivo, MAX_CARACTERES_ARCHIVO);
	recorrido->nombre_archivo[MAX_CARACTERES_ARCHIVO - 1] = '\0';
	recorrido->distancia_total = 0;
	crear_lista(&(recorrido->lista), "Recorrido");
	leer_archivo(recorrido);
}

static void leer_elemento(FILE *fp, char *elemento){
	int c = fgetc(fp);
	int posicion = 0;
	while (c != '\n' && c != EOF && posicion < MAX_CARACTERES_NODO){
		elemento[posicion] = c;
		posicion++;
		c = fgetc(fp);
	}
	if (posicion == MAX_CARACTERES_NODO){
		while (c != '\n' && c != EOF){
			c = fgetc(fp);
		}
		elemento[posicion - 1] = '\0';
	}
	elemento[posicion] = '\0';
}

bool leer_archivo(recorrido_t *recorrido){
	FILE *fp = fopen(recorrido->nombre_archivo, "r");
	if (fp == NULL){
		fprintf(stderr, "Archivo invalido\n");
		return false;
	}
	char nombre_nodo[MAX_CARACTERES_NODO];
	nombre_nodo[0] = '\0';
	while(! feof(fp)){
		leer_elemento(fp, nombre_nodo);
		if (strlen(nombre_nodo) > 0){
			printf("NODO: %s\n", nombre_nodo);
			agregar_relacion_lista(&(recorrido->lista), nombre_nodo, 0);
		}
	}

	int cierre = fclose(fp);
	if (cierre){
		fprintf(stderr, "ERROR AL CERRAR ARCHIVO DE RECORRIDO\n");
	}
	return cierre == 0;
}

void destruir_recorrido(recorrido_t *recorrido){
	destruir_lista(&(recorrido->lista));
}
