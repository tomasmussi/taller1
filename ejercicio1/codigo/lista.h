#ifndef LISTA_H

#define LISTA_H
#include <stdbool.h>
#include <stdlib.h>

// Caracteres del nombre del nodo de una tuberia
//#ifndef MAX_CARACTERES_NODO
	#define MAX_CARACTERES_NODO 21
//#endif

typedef struct nodo nodo_t;

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
bool agregar_relacion_lista(lista_t *origen, const char *otro_nodo, size_t metros);




#endif // LISTA_H
