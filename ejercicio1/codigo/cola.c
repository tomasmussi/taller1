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

nodo_t* nodo_crear(void *dato)
{
	nodo_t *nodo = malloc(sizeof(nodo_t));
	if (nodo == NULL)
		return NULL;
	nodo->dato = dato;
	nodo->siguiente = NULL;
	return nodo;
}

void nodo_destruir(nodo_t *nodo)
{
	free((void*)nodo);
}

// Crea una cola.
// Post: devuelve una nueva cola vacía.
cola_t* cola_crear()
{
	cola_t *cola = malloc(sizeof(cola_t));
	if (cola == NULL)
	{
		return NULL;
	}
	cola->primero = NULL;
	cola->ultimo = NULL;
	return cola;
}

// Destruye la cola. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la cola llama a destruir_dato.
// Pre: la cola fue creada. destruir_dato es una función capaz de destruir
// los datos de la cola, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la cola.
void cola_destruir(cola_t *cola, void destruir_dato(void*))
{
	if (!cola_esta_vacia(cola))
	{
		nodo_t *nodo = cola->primero;
		while (nodo != NULL)
		{
			if (destruir_dato != NULL)
			{
				destruir_dato(nodo->dato);
			}
			void *siguiente = nodo->siguiente;
			nodo_destruir(nodo);
			nodo = siguiente;
		}
	}
	free(cola);
}

// Devuelve verdadero o falso, según si la cola tiene o no elementos encolados.
// Pre: la cola fue creada.
bool cola_esta_vacia(const cola_t *cola)
{
	return cola->primero == NULL;
}

// Agrega un nuevo elemento a la cola. Devuelve falso en caso de error.
// Pre: la cola fue creada.
// Post: se agregó un nuevo elemento a la cola, valor se encuentra al final
// de la cola.
bool cola_encolar(cola_t *cola, void* valor)
{
	nodo_t *nodo = nodo_crear(valor);
	if (nodo == NULL)
		return false;

	if (cola_esta_vacia(cola))
	{
		cola->primero = nodo;
		cola->ultimo = nodo;
	}
	else
	{
		nodo_t *ultimo = cola->ultimo;
		ultimo->siguiente = nodo;
		cola->ultimo = nodo;
	}
	return true;
}

// Obtiene el valor del primer elemento de la cola. Si la cola tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la cola fue creada.
// Post: se devolvió el primer elemento de la cola, cuando no está vacía.
void* cola_ver_primero(const cola_t *cola)
{
	return !cola_esta_vacia(cola) ? cola->primero->dato : NULL;
}

// Saca el primer elemento de la cola. Si la cola tiene elementos, se quita el
// primero de la cola, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la cola fue creada.
// Post: se devolvió el valor del primer elemento anterior, la cola
// contiene un elemento menos, si la cola no estaba vacía.
void* cola_desencolar(cola_t *cola)
{
	void *dato = NULL;
	if (!cola_esta_vacia(cola))
	{
		nodo_t *primero = cola->primero;
		if (cola->ultimo == primero)
		{
			cola->ultimo = NULL;
		}
		cola->primero = primero->siguiente;
		dato = primero->dato;
		nodo_destruir(primero);
	}
	return dato;
}
