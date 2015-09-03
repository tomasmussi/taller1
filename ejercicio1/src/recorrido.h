#ifndef RECORRIDO_H

#define RECORRIDO_H

#include "lista.h"
#include "grafo.h"
#include "falla.h"
#include <stdlib.h>

#define MAX_CARACTERES_ARCHIVO 51
#define MAX_CARACTERES_NODO 21

typedef struct recorrido{
	char nombre_archivo[MAX_CARACTERES_ARCHIVO];
	grafo_t *grafo;
	lista_t lista;
	double distancia_total;
} recorrido_t;


/**
 * Crea un recorrido a partir de un archivo. Lo que se hace es leer todos los
 * nodos y armar el recorrido total.
 * PRE: recorrido apunta a memoria valida. Grafo fue creado y leido de archivo.
 * POST: el recorrido esta parseado con la cantidad total de metros.
 * Devuelve true si no hubo error, false de lo contrario.
 * */
bool crear_recorrido(recorrido_t *recorrido, const char *nombre_archivo,
		grafo_t *grafo);

/**
 * Destruye el recorrido.
 * PRE: recorrido fue creado.
 * */
void destruir_recorrido(recorrido_t *recorrido);

/**
 * Recibe el grafo con todas las tuberias para poder pedirle las distancias
 * del recorrido de los nodos.
 * PRE: el grafo y el recorrido fueron creados
 * POST: el recorrido ahora tiene la distancia total del recorrido
 * */
void computar_distancias(recorrido_t *recorrido);

/**
 * Reporta una falla encontrada por el recolector.
 * PRE: recorrido y falla creados.
 * */
void reportar_falla(recorrido_t *recorrido, falla_t *falla);


#endif // RECORRIDO_H
