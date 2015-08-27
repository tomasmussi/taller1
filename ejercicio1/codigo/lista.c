
#include "lista.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

struct nodo {
	char nombre[MAX_CARACTERES_NODO];
	struct nodo *siguiente;
	size_t metros;
};

nodo_t* crear_nodo(const char *nombre, size_t metros);

nodo_t* crear_nodo(const char *nombre, size_t metros){
	nodo_t *nodo = malloc(sizeof(nodo_t));
	if (nodo == NULL){
		fprintf(stderr, "SIN MEMORIA EN CREAR NODO\n");
		return NULL;
	}
	strncpy(nodo->nombre, nombre, MAX_CARACTERES_NODO);
	nodo->nombre[MAX_CARACTERES_NODO - 1] = '\0';
	nodo->siguiente = NULL;
	nodo->metros = metros;
	return nodo;
}

void destruir_nodo(nodo_t *nodo){
	free(nodo);
}

void crear_lista(lista_t *lista, const char *nombre){
	strncpy(lista->nombre, nombre, MAX_CARACTERES_NODO);
	lista->nombre[MAX_CARACTERES_NODO - 1] = '\0';
	lista->primero = NULL;
}

void destruir_lista(lista_t *lista){
	nodo_t *actual = lista->primero;
	if (actual == NULL){
		return;
	}

	while (actual != NULL){
		nodo_t *siguiente = actual->siguiente;
		destruir_nodo(actual);
		actual = siguiente;
	}
}

bool agregar_relacion_lista(lista_t *origen, const char *otro_nodo, size_t metros){
	nodo_t *nodo = origen->primero;
	if (nodo == NULL){
		nodo = crear_nodo(otro_nodo, metros);
		if (nodo == NULL) return false;
		origen->primero = nodo;
		return true;
	}
	while (nodo->siguiente != NULL){
		nodo = nodo->siguiente;
	}
	nodo->siguiente = crear_nodo(otro_nodo, metros);
	return true;	
}
