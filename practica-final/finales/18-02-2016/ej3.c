
/**
 * 3) Que funcion existe para esperar la terminacion de un thread.
 * Ejemplifique mediante un pequeño segmento de codigo.
 * 
 * 
 * 
 * Para esperar la terminacion de un thread, existe la funcion de POSIX pthread_join
 * Prototipo:
 * void pthread_join(pthread_t t, void *arg);
 * Donde pthread_t es la estructura de un thread y
 * arg es un puntero donde se puede almacenar informacion de finalizacion del
 * thread. Este argumento si es NULL se ignora.
 * 
 * Compilar: gcc -ansi -std=c99 -pthread -o prueba ej3.c
 * */
 
 #ifndef _POSIX_C_SOURCE
 #define _POSIX_C_SOURCE 1
 #endif

#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* run(void *arg);

int main(int argc, char *argv[]) {
	pthread_t t;
	memset(&t, 0, sizeof(pthread_t));
	pthread_create(&t, NULL, run, NULL);
	pthread_join(t, NULL);
	return 0;
}

void* run(void *arg) {
	for (int i = 0; i < 100; i++) {
		printf("%d\n", i);
	}
	sleep(5);
	return NULL;
}

