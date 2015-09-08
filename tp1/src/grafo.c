#include "grafo.h"
#include <stdlib.h>

#define GRAFO_TAMANIO_INICIAL 10
#define FACTOR_REDIMENSION 2

/** Redimensiona el tamanio de las listas en caso de necesitarlo */
bool redimensionar(grafo_t *grafo);

/** Crea una lista para agregar al grafo */
lista_t* alocar_lista();

/** Destruye la lista que se creo */
void desalocar_lista(lista_t *lista);

/** Agrega la relacion dirigida origen -> destino */
bool agregar_relacion_dirigida(grafo_t *grafo, const char *origen, 
		const char *destino, double metros);

/** Al ser un grafo no dirigido, se agrega A -> B como B -> A */
bool agregar_relacion(grafo_t *grafo, const char *nodo_a, const char *nodo_b, 
		double metros);

bool crear_grafo(grafo_t *grafo, const char *tuberias){
	grafo->vector = calloc(GRAFO_TAMANIO_INICIAL, sizeof(lista_t));	
	if (grafo->vector == NULL){
		fprintf(stderr, "SIN MEMORIA EN CREAR GRAFO\n");
		return false;
	}
	strncpy(grafo->nombre_archivo, tuberias, MAX_CARACTERES_ARCHIVO);
	grafo->nombre_archivo[MAX_CARACTERES_ARCHIVO - 1] = '\0';
	grafo->cantidad = 0;
	grafo->tamanio = GRAFO_TAMANIO_INICIAL;
	return true;
}

void destruir_grafo(grafo_t *grafo){
	for (size_t posicion = 0; posicion < grafo->cantidad; posicion++){
		destruir_lista(grafo->vector[posicion]);
		desalocar_lista(grafo->vector[posicion]);
	}
	free(grafo->vector);
}

bool agregar_relacion(grafo_t *grafo, const char *nodo_a, const char *nodo_b, 
		double metros){
	bool r1 = agregar_relacion_dirigida(grafo, nodo_a, nodo_b, metros);
	bool r2 = agregar_relacion_dirigida(grafo, nodo_b, nodo_a, metros);
	return r1 && r2;
}

/** Busca el nodo en la lista de adyacencias del grafo */
size_t buscar(grafo_t *grafo, const char *nodo){
	size_t posicion = 0;
	while (posicion < grafo->cantidad){
		if (strcmp(nodo, grafo->vector[posicion]->nombre) == 0){
			return posicion;
		} else {
			posicion++;
		}
	}
	return posicion;
}


bool agregar_relacion_dirigida(grafo_t *grafo, const char *origen, 
		const char *destino, double metros){
	size_t posicion = buscar(grafo, origen);
	if (posicion == grafo->cantidad){
		// No lo encontre en el vector, hay que agregarlo a la lista
		if (grafo->cantidad == grafo->tamanio){
			bool pudo_redimensionar = redimensionar(grafo);
			if (!pudo_redimensionar) return false;
		}
		lista_t *lista = alocar_lista();
		if (!lista) return false;
		crear_lista(lista, origen);
		grafo->vector[posicion] = lista;
		grafo->cantidad++;
	}
	agregar_relacion_lista(grafo->vector[posicion], destino, metros);
	return true;
}

bool redimensionar(grafo_t *grafo){
	lista_t **nuevo_vector = realloc(grafo->vector, 
			FACTOR_REDIMENSION * grafo->tamanio);
	if (nuevo_vector == NULL){
		fprintf(stderr, "NO SE PUDO REDIMENSIONAR EL GRAFO\n");
		return false;
	}
	grafo->vector = nuevo_vector;
	grafo->tamanio = FACTOR_REDIMENSION * grafo->tamanio;
	return true;
}

lista_t* alocar_lista(){
	lista_t *lista = malloc(sizeof(lista_t));
	if (lista == NULL){
		fprintf(stderr, "SIN MEMORIA CREANDO UNA LISTA PARA EL GRAFO\n");
		return NULL;
	}
	return lista;
}

void desalocar_lista(lista_t *lista){
	free(lista);
}

static void leer_elemento(FILE *fp, char *elemento){
	int c = fgetc(fp);
	int posicion = 0;
	while (c != ',' && c != '\n' && c != EOF && posicion < MAX_CARACTERES_NODO){
		elemento[posicion] = c;
		posicion++;
		c = fgetc(fp);
	}
	if (posicion == MAX_CARACTERES_NODO){
		while (c != ',' && c != '\n' && c != EOF){
			c = fgetc(fp);
		}
		elemento[posicion - 1] = '\0';
	}
	elemento[posicion] = '\0';
}

bool valores_validos(const char *elemento1, const char *elemento2, 
		const char *elemento3){
	return strlen(elemento1) > 0 && strlen(elemento2) > 0 && 
		strlen(elemento3) > 0;
}

bool armar_grafo_archivo(grafo_t *grafo){
	FILE *fp = fopen(grafo->nombre_archivo, "r");
	if (fp == NULL){
		fprintf(stderr, "Archivo inválido\n");
		return false;
	}
	char nombre_a[MAX_CARACTERES_NODO];
	char nombre_b[MAX_CARACTERES_NODO];
	char distancia[MAX_CARACTERES_NODO];
	nombre_a[0] = '\0';
	nombre_b[0] = '\0';
	distancia[0] = '\0';
	bool ok = true;
	while(! feof(fp)){
		leer_elemento(fp, nombre_a);
		leer_elemento(fp, distancia);
		leer_elemento(fp, nombre_b);
		double distancia_real = atof(distancia);
		if (valores_validos(nombre_a, nombre_b, distancia)){
			ok &= agregar_relacion(grafo, nombre_a, nombre_b, distancia_real);
		}
	}
	int cierre = fclose(fp);
	if (cierre){
		fprintf(stderr, "ERROR AL CERRAR ARCHIVO DE RECORRIDO\n");
	}
	return cierre == 0 && ok;
}

double obtener_distancia_nodos(grafo_t *grafo, const char *nodo_a, 
		const char *nodo_b){
	size_t posicion = buscar(grafo, nodo_a);
	if (posicion != grafo->cantidad){
		return buscar_en_lista(grafo->vector[posicion], nodo_b);
	}
	return 0;
}
