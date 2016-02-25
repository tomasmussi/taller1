/**
 * 6) Escriba un programa ISO C multithread que irremediablemente conduzca
 * al deadlock.
 * 
 * 
 * 
 * Deadlock: se produce cuando dos o mas hilos bloquearon un recurso y necesitan
 * otro recurso que esta bloqueado por otro hilo.
 * 
 * Compilar: gcc -ansi -std=c99 -pthread -o prueba ej6.c
 * */


#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 1
#endif

#include <string.h>
#include <stdio.h>
#include <pthread.h>


void* run (void *arg);

int main(int argc, char *argv[]) {
	pthread_mutex_t m;
	pthread_mutex_init(&m, NULL);
	pthread_mutex_lock(&m); // MAIN BLOQUEA MUTEX
	pthread_t h;
	pthread_create(&h, NULL, run, &m); // Disparo nuevo hilo y le paso el mutex
	printf("[MAIN]Esperando que termine la ejecucion el hilo disparado\n");
	pthread_join(h, NULL); // Espero al hilo
	// Libero recursos
	printf("Esto nunca se ejecutara\n");
	pthread_mutex_unlock(&m);
	pthread_mutex_destroy(&m);
	return 0;
}


void* run (void *arg) {
	pthread_mutex_t *m = (pthread_mutex_t*) arg; // Se que me pasaron un mutex
	pthread_mutex_lock(m);
	printf("[HILO SECUNDARIO]Tengo el mutex\n");
	pthread_mutex_unlock(m);
	return NULL;
}
