/*
3)
Haciendo uso de un arreglo estático de 1000 posiciones, implemente una pila de enteros. 
* La librería debe contemplar su uso en ambientes multithreading. 
* Por consiguiente se espera que incorpore los recursos necesarios 
* para garantizar la coherencia de la estructura en todo momento.
*/ 

#define MAX 1000
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

class Pila {
public:
	Pila() : indice(0) {
		memset(&mutex, 0, sizeof(pthread_mutex_t));
		pthread_mutex_init(&mutex, NULL);
	}
	~Pila() {
		pthread_mutex_destroy(&mutex);
	}
	void push(int numero) {
		pthread_mutex_lock(&mutex);
		if (indice < MAX)
			arreglo[indice++] = numero;
		pthread_mutex_unlock(&mutex);
	}
	int ver_tope() {
		pthread_mutex_lock(&mutex);
		int resultado = arreglo[indice - 1];
		pthread_mutex_unlock(&mutex);
		return resultado;
	}
	void sacar(){
		pthread_mutex_lock(&mutex);
		if (indice > 0)
			indice--;
		pthread_mutex_unlock(&mutex);
	}
	bool vacio() {
		pthread_mutex_lock(&mutex);
		bool rta = indice - 1 == 0;
		pthread_mutex_unlock(&mutex);
		return rta;
	}
private:
	int arreglo[MAX];
	int indice;
	pthread_mutex_t mutex;
};

void* callback(void *data) {
	Pila *p = (Pila*) data;
	for (int i = 0; i < 100; i++) {
		p->push(i);
	}
	return NULL;
}


int main(int argc, char *argv[]) {
	
	Pila p;
	p.push(3);
	p.push(6);
	p.push(9);
	std::cout << "Tope 9 = " << p.ver_tope() << std::endl;
	p.sacar();
	std::cout << "Tope 6 = " << p.ver_tope() << std::endl;
	std::cout << "Vacio: " << (p.vacio() ? "ERROR" : "OK") << std::endl;
	p.sacar();
	std::cout << "Tope 3 = " << p.ver_tope() << std::endl;
	std::cout << "Vacio: " << (p.vacio() ? "OK" : "ERROR") << std::endl;
	pthread_t h1;
	pthread_t h2;
	pthread_create(&h1, NULL, callback, (void*) &p);
	pthread_create(&h2, NULL, callback, (void*) &p);
	pthread_join(h1, NULL);
	pthread_join(h2, NULL);
	
	int count = 0;
	while (! p.vacio()) {
		count++;
		std::cout << "tope: " << p.ver_tope() << std::endl;
		p.sacar();
	}
	std::cout << "Cuenta: " << count << std::endl;
	return 0;
}

