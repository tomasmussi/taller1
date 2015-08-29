
#include "lista.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

struct nodo {
	char nombre[MAX_CARACTERES_NODO];
	struct nodo *siguiente;
	double metros;
};

nodo_t* crear_nodo(const char *nombre, double metros);

nodo_t* crear_nodo(const char *nombre, double metros){
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

bool agregar_relacion_lista(lista_t *origen, const char *otro_nodo, double metros){
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

size_t buscar_en_lista(lista_t *lista, const char *nodo_destino){
	if (lista->primero == NULL) return 0;
	nodo_t *nodo = lista->primero;
	while (nodo != NULL){
		if (strcmp(nodo->nombre, nodo_destino) == 0) {
			return nodo->metros;
		} else {
			nodo = nodo->siguiente;
		}
	}
	return 0;
}

void crear_iterador(lista_t *lista, iter_t *it){
	it->actual = lista->primero;
	it->anterior = NULL;
}

bool iterador_al_final(const iter_t *it){
	return (it->actual == NULL);
}

char* iterador_ver_actual(const iter_t *it){
	return iterador_al_final(it) ? NULL : it->actual->nombre;
}

bool iterador_avanzar(iter_t *it){
	if (!iterador_al_final(it)) {
		it->anterior = it->actual;
		it->actual = it->actual->siguiente;
		return true;
	} else {
		return false;
	}
}

void destruir_iterador(iter_t *it){
	it->actual = NULL;
	it->anterior = NULL;
}

const char* it_nombre(iter_t *it){
	return it->actual->nombre;
}
