#ifndef COLA_H
#define COLA_H

#include <stdbool.h>
#include <stddef.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

typedef struct cola cola_t;

/* ******************************************************************
 *                    PRIMITIVAS DE LA COLA
 * *****************************************************************/

/**
 * Crea una cola.
 * Post: devuelve una cola vacia
 * */
cola_t* cola_crear();

/** Destruye la cola. Si se recibe la funcion destruir_dato por 
 * parametro, para cada uno de los elementos de la cola llama a 
 * destruir_dato.
 * Pre: la cola fue creada. destruir_dato es una función capaz de 
 * destruir los datos de la cola, o NULL en caso de que no se la utilice
 * Post: se eliminaron todos los elementos de la cola.
 **/
void cola_destruir(cola_t *cola, void destruir_dato(void*));

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
 * Obtiene el valor del primer elemento de la cola. Si la cola tiene
 * elementos, se devuelve el valor del primero, si está vacía devuelve 
 * NULL.
 * Pre: la cola fue creada.
 * Post: se devolvio el primer elemento de la cola, cuando no esta vacia
 * */
void* cola_ver_primero(const cola_t *cola);

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
