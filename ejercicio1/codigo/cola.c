#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include "cola.h"

/* Estructuras */
typedef struct nodo_cola{
	void *dato;
	struct nodo_cola *siguiente;
} nodo_t;

struct cola{
	nodo_t *primero;
	nodo_t *ultimo;
};

/* Fin estructuras */

/* Declaracion de funciones */

nodo_t* nodo_crear(void *dato);

void nodo_destruir(nodo_t *nodo);

/* Fin declaracion de funciones */

nodo_t* nodo_crear(void *dato){
	nodo_t *nodo = malloc(sizeof(nodo_t));
	if (nodo == NULL){
		return NULL;
	}
	nodo->dato = dato;
	nodo->siguiente = NULL;
	return nodo;
}

void nodo_destruir(nodo_t *nodo){
	free((void*)nodo);
}

cola_t* cola_crear(){
	cola_t *cola = malloc(sizeof(cola_t));
	if (cola == NULL){
		return NULL;
	}
	cola->primero = NULL;
	cola->ultimo = NULL;
	return cola;
}

void cola_destruir(cola_t *cola){
	if (!cola_esta_vacia(cola)){
		nodo_t *nodo = cola->primero;
		while (nodo != NULL){
			void *siguiente = nodo->siguiente;
			nodo_destruir(nodo);
			nodo = siguiente;
		}
	}
	free(cola);
}

bool cola_esta_vacia(const cola_t *cola){
	return cola->primero == NULL;
}

bool cola_encolar(cola_t *cola, void* valor){
	nodo_t *nodo = nodo_crear(valor);
	if (nodo == NULL){
		return false;
	}
	if (cola_esta_vacia(cola)){
		cola->primero = nodo;
		cola->ultimo = nodo;
	} else {
		nodo_t *ultimo = cola->ultimo;
		ultimo->siguiente = nodo;
		cola->ultimo = nodo;
	}
	return true;
}

void* cola_ver_primero(const cola_t *cola){
	return !cola_esta_vacia(cola) ? cola->primero->dato : NULL;
}

void* cola_desencolar(cola_t *cola){
	void *dato = NULL;
	if (!cola_esta_vacia(cola)){
		nodo_t *primero = cola->primero;
		if (cola->ultimo == primero){
			cola->ultimo = NULL;
		}
		cola->primero = primero->siguiente;
		dato = primero->dato;
		nodo_destruir(primero);
	}
	return dato;
}
