#ifndef COLA_H
#define COLA_H

#include <stdbool.h>
#include <stddef.h>

typedef struct cola cola_t;

/**
 * Crea una cola.
 * Post: devuelve una cola vacia
 * */
cola_t* crear_cola();

/** 
 * Destruye la cola.
 * Pre: la cola fue creada.
 * Post: se eliminaron todos los elementos de la cola.
 **/
void destruir_cola(cola_t *cola);

/**
 * Devuelve verdadero o false, segun si la cola tiene o no elementos
 * Pre: la cola fue creada
 * */
bool cola_esta_vacia(const cola_t *cola);

/**
 * Agrega un nuevo elemento a la cola. Devuelve falso en caso de error.
 * Pre: la cola fue creada.
 * Post: se agrego un nuevo elemento a la cola, valor se encuentra al 
 * final de la cola.
 * */
bool cola_encolar(cola_t *cola, void* valor);

/**
 * Saca el primer elemento de la cola. Si la cola tiene elementos, se 
 * quita el primero de la cola, y se devuelve su valor, si está vacia, 
 * devuelve NULL.
 * Pre: la cola fue creada.
 * Post: se devolvio el valor del primer elemento anterior, la cola
 * contiene un elemento menos, si la cola no estaba vacia.
 * */
void* cola_desencolar(cola_t *cola);

#endif // COLA_H
