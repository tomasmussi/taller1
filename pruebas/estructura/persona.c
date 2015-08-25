#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "persona.h"


struct persona {
	char nombre[8];
	int edad;
};


per_t* crear(){
	per_t* persona = malloc(sizeof(per_t));
	if (persona == NULL){
		printf("Sin memoria\n");
		return NULL;
	}
	strcpy(persona->nombre, "Tomas");
	persona->edad = 24;
	return persona;
}


void destruir(per_t *persona){
	free(persona);
}

void setEdad(per_t *persona, int edad){
	persona->edad = edad;
}

void imprimir(per_t *persona){
	printf("Nombre: %s\n", persona->nombre);
	printf("Edad: %d\n", persona->edad);
}


