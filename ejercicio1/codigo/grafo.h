
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
 * POST: grafo inicializado y listo para agregar nodos
 * */
void crear_grafo(grafo_t *grafo, const char *tuberias);

/**
 * Destruye el grafo
 * PRE: grafo es una direccion de memoria valida
 * POST: se destruyen todas las estructuras internas y se libera la memoria ocupada
 * */
void destruir_grafo(grafo_t *grafo);

/**
 * Agrega un conexion entre 2 nodos
 * TODO: TAL VEZ DEBERIA SER PRIVADO, TOTAL LO QUE IMPORTA ES QUE SE LEA EL ARCHIVO
 * Y EL GRAFO SE ARME INTERNAMENTE USANDO ESTA FUNCION
 * PRE: el grafo fue creado
 * POST: relacion agregada entre a->b y b->a con la cantidad de metros especificada
 * */
bool agregar_relacion(grafo_t *grafo, const char *nodo_a, const char *nodo_b, 
		double metros);

bool armar_grafo_archivo(grafo_t *grafo, const char *nombre_archivo);

double obtener_distancia_nodos(grafo_t *grafo, const char *nodo_a, 
		const char *nodo_b);

#endif // GRAFO_H
