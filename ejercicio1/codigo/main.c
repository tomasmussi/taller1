
#include <stdio.h>
#include "grafo.h"

#define CANTIDAD_ARCHIVOS 4

void prueba_grafo(){
	grafo_t grafo_reservado;
	grafo_t *grafo = &grafo_reservado;
	crear_grafo(grafo);
	agregar_relacion(grafo, "A", "B", 100);
	agregar_relacion(grafo, "B", "C", 200);
	agregar_relacion(grafo, "C", "D", 900);
	agregar_relacion(grafo, "D", "E", 400);
	agregar_relacion(grafo, "C", "E", 800);
	destruir_grafo(grafo);
}

int main(int argc, char *argv[]){
	/*if (argc != CANTIDAD_ARCHIVOS){
		printf("Error, cantidad de archivos invalida\n");
		return 1;
	}
	*/
	prueba_grafo();
	return 0;
}


