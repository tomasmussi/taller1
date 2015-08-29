#ifndef RECORRIDO_H

#define RECORRIDO_H
#include "lista.h"
#include "grafo.h"
#include "cola.h"
#include "falla.h"
#include <stdlib.h>
#define MAX_CARACTERES_ARCHIVO 51
#define MAX_CARACTERES_NODO 21

typedef struct recorrido{
	char nombre_archivo[MAX_CARACTERES_ARCHIVO];
	lista_t lista;
	double distancia_total;
} recorrido_t;


/**
 * Crea un recorrido a partir de un archivo. Lo que se hace es leer todos los
 * nodos y armar el recorrido total
 * PRE: recorrido apunta a una estructura valida.
 * POST: el recorrido esta parseado con la cantidad total de metros.
 * Si el nombre de archivo a leer es invalido, se informa un error.
 * */
void crear_recorrido(recorrido_t *recorrido, const char *nombre_archivo);

/**
 * Destruye el TDA
 * PRE: recorrido fue creado
 * POST: el recorrido fue destruido y no puede usarse
 * */
void destruir_recorrido(recorrido_t *recorrido);

/**
 * Recibe el grafo con todas las tuberias para poder pedirle las distancias
 * del recorrido de los nodos.
 * PRE: el grafo y el recorrido fueron creados
 * POST: el recorrido ahora tiene la distancia total del recorrido
 * */
void computar_distancias(recorrido_t *recorrido, grafo_t *grafo);

void informar_fallas(recorrido_t *recorrido, grafo_t *grafo, cola_t *cola);


#endif // RECORRIDO_H
