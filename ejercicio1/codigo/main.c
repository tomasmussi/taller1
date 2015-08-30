
#include <stdio.h>
#include "grafo.h"
#include "recorrido.h"
#include "recolector.h"

#define CANTIDAD_ARCHIVOS 4

bool ejecutar(const char *mediciones, const char *tuberias, 
		const char *recorrido_archivo){
	recolector_t recolector_reservado;
	recolector_t *recolector = &recolector_reservado;
	grafo_t grafo_reservado;
	grafo_t *grafo = &grafo_reservado;
	recorrido_t recorrido_reservado;
	recorrido_t *recorrido = &recorrido_reservado;

	crear_recorrido(recorrido, recorrido_archivo);
	bool ok = crear_grafo(grafo, tuberias);
	if (!ok){
		destruir_recorrido(recorrido);
		destruir_grafo(grafo);
		return true;
	}
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
	bool resultado = ejecutar(argv[1], argv[2], argv[3]);
	return resultado ? 1 : 0;
}

