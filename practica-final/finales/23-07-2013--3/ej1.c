/*
1)
Escriba:

La definición de una función de alcance local al archivo de definición, denominada suma que tome como parámetros 2 enteros y devuelva un puntero a caracter con el resultado de la suma formateada como una cadena.

La declaración de un puntero a una función que toma como parámetros un entero corto sin signo y un puntero a puntero a entero y devuelve un número de punto flotante.

La definición de un puntero a puntero a entero.*/

#include <stdio.h>
#include <stdlib.h>

// i)
static char* suma(int a, int b) {
	char *ptr = (char*) malloc(50 * sizeof(char));
	sprintf(ptr, "%d + %d", a, b);
	return ptr;
}

// ii)
float (*funcion)(unsigned short a, int **b);

// iii)
int **p;

float asd(unsigned short a, int **b) {
	printf("llamada\n");
}


int main() {
	char *p = suma(10, 20);
	printf("Resultado: %s\n", p);
	free(p);
	funcion = asd;
	int *entero;
	funcion(1, &entero);
	return 0;
}
