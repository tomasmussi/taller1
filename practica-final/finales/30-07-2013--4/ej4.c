/*
4) Explique el propósito de la función pthread_join. Ejemplifique.

El proposito de pthread join es, luego de haberse bifurcado un hilo en dos, tienen que volver a sincronizarse.
Digamos que el hilo main de una aplicacion despacha un hilo worker. Dicho hilo worker hara su trabajo,
pero el hilo main no puede finalizar sin que el worker haya terminado, porque el worker quedaria sin hilo
padre.
Entonces el hilo main hace una llamada a pthread_join con la estructura con la que se hizo pthread_create
y ademas se le puede pasar un segundo parametro para obtener informacion de la terminacion del hilo worker.
Al llamar a pthread_join, el hilo main se queda bloqueado hasta que el hilo worker termine su ejecucion.
Una vez terminada la ejecucion, se desbloquea la llamada a pthread_join y se continua con la siguiente instruccion.

Compilar gcc -ansi -std=c99 -pthread -o prueba ej4.c
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* worker(void *data) {
	int *i = (int*) data;
	printf("Parametro: %d\n", *i);
	for (int i = 0; i < 10; i++) {
		printf("I: %d\n", i);
	}
	return NULL;
}

int main() {
	pthread_t thread;
	int i = 24;
	pthread_create(&thread, NULL, worker, (void*) &i);
	sleep(3); // 3 segundos para darle prioridad al otro thread
	printf("Yo imprimo otro i: %d\n", i);
	pthread_join(thread, NULL);
	return 0;
}


