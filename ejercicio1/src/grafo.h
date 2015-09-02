
#ifndef GRAFO_H

#define GRAFO_H

#include "lista.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct grafo {
	lista_t **vector;
	size_t cantidad;
	size_t tamanio;
} grafo_t;

/**
 * Crea el grafo. Es un grafo no dirigido y pesado (con las distancias
 * que separan nodos como pesos)
 * PRE: grafo es una direccion de memoria valida
 * POST: devuelve true si el grafo esta inicializado y listo para agregar nodos
 * false si hubo un error al leer el archivo
 * */
bool crear_grafo(grafo_t *grafo, const char *tuberias);

/**
 * Destruye el grafo
 * PRE: grafo es una direccion de memoria valida
 * POST: se destruyen todas las estructuras internas y se libera la memoria ocupada
 * */
void destruir_grafo(grafo_t *grafo);

/**
 * Lee el archivo "nombre_archivo" y crea el grafo desde ahi.
 * El archivo tiene el formato: nodo1,distancia,nodo2.
 * Ej: A,400,B
 * PRE: grafo apunta a una estructura valida
 * POST: el grafo tiene cargadas todas las direcciones
 * */
bool armar_grafo_archivo(grafo_t *grafo, const char *nombre_archivo);

/**
 * Obtiene la distancia que separa dos nodos.
 * PRE: grafo apunta a una estructura valida
 * POST: devuelve la distancia que separa a los nodos. Si no existe la relacion
 * devuelve 0.
 * */
double obtener_distancia_nodos(grafo_t *grafo, const char *nodo_a, 
		const char *nodo_b);

#endif // GRAFO_H
