

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

void computar_distancias(recorrido_t *recorrido, grafo_t *grafo){
	recorrido->distancia_total = 0;
	iter_t iterador_anterior_reservado;
	iter_t iterador_actual_reservado;
	iter_t *it_anterior = &iterador_anterior_reservado;
	iter_t *it_actual = &iterador_actual_reservado;
	crear_iterador(&(recorrido->lista), it_anterior);
	crear_iterador(&(recorrido->lista), it_actual);
	bool avanzo = iterador_avanzar(it_actual);
	if (!avanzo){
		return;
	}
	while (!iterador_al_final(it_actual)){
		recorrido->distancia_total += obtener_distancia_nodos(grafo, it_nombre(it_anterior), it_nombre(it_actual));
		iterador_avanzar(it_anterior);
		iterador_avanzar(it_actual);
	}
}

void reportar_falla(recorrido_t *recorrido, grafo_t *grafo, falla_t *falla){
	double punto = falla->punto_recorrido;
	iter_t iterador_anterior_reservado;
	iter_t iterador_actual_reservado;
	iter_t *it_anterior = &iterador_anterior_reservado;
	iter_t *it_actual = &iterador_actual_reservado;
	crear_iterador(&(recorrido->lista), it_anterior);
	crear_iterador(&(recorrido->lista), it_actual);
	bool avanzo = iterador_avanzar(it_actual);
	if (!avanzo){
		return;
	}
	bool reportado = false;
	while (!iterador_al_final(it_actual) && !reportado){
		double tramo = obtener_distancia_nodos(grafo, it_nombre(it_anterior), it_nombre(it_actual));
		if (tramo > punto){
			printf("%s %s->%s (%.2fm)\n", falla->tipo, 
										it_nombre(it_anterior), 
										it_nombre(it_actual),
										punto);
			reportado = true;
		} else {
			punto -= tramo;
		}
		iterador_avanzar(it_anterior);
		iterador_avanzar(it_actual);
	}
}

void informar_fallas(recorrido_t *recorrido, grafo_t *grafo, cola_t *cola){
	while(! cola_esta_vacia(cola)){
		falla_t *falla = cola_desencolar(cola);
		reportar_falla(recorrido, grafo, falla);
		destruir_falla(falla);
	}
}

