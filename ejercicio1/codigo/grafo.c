
#include "grafo.h"
#include <stdlib.h>


#define GRAFO_TAMANIO_INICIAL 10
#define FACTOR_REDIMENSION 2


bool redimensionar(grafo_t *grafo);
lista_t* alocar_lista();
void desalocar_lista(lista_t *lista);
bool agregar_relacion_dirigida();

void crear_grafo(grafo_t *grafo){
	grafo->vector = calloc(GRAFO_TAMANIO_INICIAL, sizeof(lista_t));
	if (grafo->vector == NULL){
		fprintf(stderr, "SIN MEMORIA EN CREAR GRAFO\n");
		return;
	}
	grafo->cantidad = 0;
	grafo->tamanio = GRAFO_TAMANIO_INICIAL;
}

void destruir_grafo(grafo_t *grafo){
	for (size_t posicion = 0; posicion < grafo->cantidad; posicion++){
		destruir_lista(grafo->vector[posicion]);
		desalocar_lista(grafo->vector[posicion]);
	}
	free(grafo->vector);
}

/**
 * Hay que agregar las relaciones a->b y b->a que son iguales, lo separo en otra funcion
 * */
bool agregar_relacion(grafo_t *grafo, const char *nodo_a, const char *nodo_b, size_t metros){
	agregar_relacion_dirigida(grafo, nodo_a, nodo_b, metros);
	agregar_relacion_dirigida(grafo, nodo_b, nodo_a, metros);
	return true;
}


bool agregar_relacion_dirigida(grafo_t *grafo, const char *origen, const char *destino, size_t metros){
	// Busco el origen en el vector de listas
	bool encontrado = false;
	size_t posicion = 0;
	while (!encontrado && (posicion < grafo->cantidad)){
		if (strcmp(origen, grafo->vector[posicion]->nombre) == 0){
			encontrado = true;
		} else {
			posicion++;
		}
	}
	if (!encontrado){
		// No lo encontre en el vector, hay que agregarlo a la lista
		if (grafo->cantidad == grafo->tamanio){
			bool pudo_redimensionar = redimensionar(grafo);
			if (!pudo_redimensionar) return false;
		}
		lista_t *lista = alocar_lista();
		if (!lista) return false;
		crear_lista(lista, origen);
		grafo->vector[posicion] = lista;
		grafo->cantidad++;
	}
	agregar_relacion_lista(grafo->vector[posicion], destino, metros);
	return true;
}

bool redimensionar(grafo_t *grafo){
	lista_t **nuevo_vector = realloc(grafo->vector, FACTOR_REDIMENSION * grafo->tamanio);
	if (nuevo_vector == NULL){
		fprintf(stderr, "NO SE PUDO REDIMENSIONAR EL GRAFO\n");
		return false;
	}
	grafo->vector = nuevo_vector;
	grafo->tamanio = FACTOR_REDIMENSION * grafo->tamanio;
	return true;
}

lista_t* alocar_lista(){
	lista_t *lista = malloc(sizeof(lista_t));
	if (lista == NULL){
		fprintf(stderr, "SIN MEMORIA CREANDO UNA LISTA PARA EL GRAFO\n");
		return NULL;
	}
	return lista;
}

void desalocar_lista(lista_t *lista){
	free(lista);
}

