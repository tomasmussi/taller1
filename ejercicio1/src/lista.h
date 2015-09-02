#ifndef LISTA_H

#define LISTA_H
#include <stdbool.h>
#include <stdlib.h>

// Caracteres del nombre del nodo de una tuberia
#define MAX_CARACTERES_NODO 21

typedef struct nodo nodo_t;

typedef struct iterador {
	nodo_t *actual;
	nodo_t *anterior;
} iter_t;

typedef struct lista {
	char nombre[MAX_CARACTERES_NODO];
	nodo_t *primero;
} lista_t;

/**
 * Crea una lista correspondiente al nodo de nombre nombre
 * PRE: lista es un puntero a una estructura valida
 * POST: lista creada con el nombre
 * */
void crear_lista(lista_t *lista, const char *nombre);

/**
 * Destruye la lista con todos sus elementos
 * */
void destruir_lista(lista_t *lista);

/**
 * Agrega la relacion del nodo origen con el otro nodo.
 * Tambien incluye los metros que los conectan
 * PRE: lista es un puntero a una estructura valida
 * POST: nodos desde origen a destino conectados (Recordar hacer la otra conexion)
 */
bool agregar_relacion_lista(lista_t *origen, const char *otro_nodo, 
	double metros);

size_t buscar_en_lista(lista_t *lista, const char *nodo_destino);

/** Primitivas del iterador de lista para buscar elementos */

/**
 * Crea un iterador que apunta al primer elemento de la lista
 * */
void crear_iterador(lista_t *lista, iter_t *it);

/**
 * Informa si el iterador esta al final de la lista
 * */
bool iterador_al_final(const iter_t *it);

/**
 * Avanza hacia el siguiente elemento. Si avanzo al siguiente devuelve true.
 * Si ya estaba al final de la lista, devuelve false.
 * */
bool iterador_avanzar(iter_t *it);

/**
 * Destruye el iterador para que no se pueda utilizar mas.
 * */
void destruir_iterador(iter_t *it);

/**
 * Devuelve el nombre del nodo actual de la lista
 * */
const char* it_nombre(iter_t *it);

#endif // LISTA_H
