
#include <stdio.h>
#include "grafo.h"
#include "recorrido.h"
#include "recolector.h"

#define CANTIDAD_ARCHIVOS 4

/*
 * PRUEBA DEPRECADA
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
*/
void prueba_grafo_archivo(const char *nombre_archivo){
	grafo_t grafo_reservado;
	grafo_t *grafo = &grafo_reservado;
	crear_grafo(grafo, nombre_archivo);
	destruir_grafo(grafo);
}

void prueba_recorrido(const char *archivo){
	recorrido_t recorrido_reservado;
	recorrido_t *recorrido = &recorrido_reservado;
	crear_recorrido(recorrido, archivo);
	destruir_recorrido(recorrido);
}

void prueba_grafo_recorrido(const char *tuberias, 
		const char *recorrido_archivo){
	grafo_t grafo_reservado;
	grafo_t *grafo = &grafo_reservado;
	recorrido_t recorrido_reservado;
	recorrido_t *recorrido = &recorrido_reservado;

	crear_grafo(grafo,tuberias);
	crear_recorrido(recorrido, recorrido_archivo);
	
	computar_distancias(recorrido, grafo);
	destruir_recorrido(recorrido);
	destruir_grafo(grafo);
}


void prueba_recolector(const char *datos_recolectados){
	recolector_t recolector_reservado;
	recolector_t *recolector = &recolector_reservado;
	crear_recolector(recolector, datos_recolectados, 4);
	destruir_recolector(recolector);
}

bool ejecutar(const char *mediciones, const char *tuberias, 
		const char *recorrido_archivo){
	recolector_t recolector_reservado;
	recolector_t *recolector = &recolector_reservado;
	grafo_t grafo_reservado;
	grafo_t *grafo = &grafo_reservado;
	recorrido_t recorrido_reservado;
	recorrido_t *recorrido = &recorrido_reservado;

	crear_recorrido(recorrido, recorrido_archivo);
	crear_grafo(grafo, tuberias);
	computar_distancias(recorrido, grafo);
	crear_recolector(recolector, mediciones, recorrido->distancia_total);
	bool error = procesar_archivo(recolector);	
	informar_fallas(recorrido, grafo, recolector->fallas);

	destruir_recorrido(recorrido);
	destruir_grafo(grafo);
	destruir_recolector(recolector);
	return error;
}

int main(int argc, char *argv[]){
	if (argc != CANTIDAD_ARCHIVOS){
		fprintf(stderr, "Error, cantidad de archivos invalida\n");
		return 1;
	}

	/*prueba_grafo();
	prueba_grafo_archivo(argv[2]);
	prueba_recorrido(argv[3]);
	prueba_grafo_recorrido(argv[2], argv[3]);
	prueba_recolector(argv[1]);*/
	bool resultado = ejecutar(argv[1], argv[2], argv[3]);
	return resultado ? 1 : 0;
}

