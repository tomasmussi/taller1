#ifndef GRAFO_H

#define GRAFO_H

#include "lista.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_CARACTERES_ARCHIVO 51

typedef struct grafo {
	lista_t **vector;
	char nombre_archivo[MAX_CARACTERES_ARCHIVO];
	size_t cantidad;
	size_t tamanio;
} grafo_t;

/**
 * Crea un grafo no dirigido y pesado (con las distancias que separan nodos como pesos)
 * Al crear el grafo directamente se lee el archivo.
 * PRE: grafo apunta a memoria reservada.
 * POST: devuelve true si el grafo esta inicializado y listo para agregar nodos
 * false de lo contrario.
 * */
bool crear_grafo(grafo_t *grafo, const char *tuberias);

/**
 * Destruye el grafo
 * PRE: el grafo fue creado.
 * POST: se destruyen todas las estructuras internas y se libera la memoria ocupada
 * */
void destruir_grafo(grafo_t *grafo);

/**
 * Lee el archivo de tuberias y agrega las relaciones al grafo.
 * El archivo tiene el formato: nodo1,distancia,nodo2.
 * Ej: A,400,B
 * PRE: el grafo fue creado.
 * POST: el grafo tiene cargadas todas las relaciones.
 * */
bool armar_grafo_archivo(grafo_t *grafo);

/**
 * Obtiene la distancia que separa dos nodos.
 * PRE: el grafo fue creado.
 * POST: devuelve la distancia que separa a los nodos. Si no existe la relacion
 * devuelve 0.
 * */
double obtener_distancia_nodos(grafo_t *grafo, const char *nodo_a, 
		const char *nodo_b);

#endif // GRAFO_H
