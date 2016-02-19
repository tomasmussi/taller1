/**
 * Ejemplo basico de primitivas de thread de POSIX
 * Compilar con: gcc -ansi -std=c99 -pthread -o thread main.c
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <pthread.h>

pthread_mutex_t mutex;

void init() {
	memset(&mutex, 0, sizeof(pthread_mutex_t));
	pthread_mutex_init(&mutex, NULL);
}

void destroy() {
	pthread_mutex_destroy(&mutex);
}

void* run(void *data) {
	pthread_mutex_lock(&mutex);
	printf("Imprimiendo hilo: %d\n", *((int*)data));
	pthread_mutex_unlock(&mutex);
	return NULL;
}


void procesar(int numero) {
	pthread_t hilos[numero];
	for (int i = 0; i < numero; i++) {
		memset(hilos + i, 0, sizeof(pthread_t));
		pthread_create(hilos + i, NULL, run, (void*) (&i));
	}

	for (int i = 0; i < numero; i++) {
		pthread_join(hilos[i], NULL);
	}
}


int main(int argc, char *argv[]) {
	int threads = 10;
	if (argc > 1)
		threads = atoi(argv[1]);
	printf("Numero de threads: %d\n", threads);
	init();
	procesar(threads);
	return 0;
}
