/*
7)
¿Qué objeto se provee en ISO C para manejar la consola de entrada?Ejemplifique.

El objeto que se provee se llama 'stdin' y es un File pointer al buffer de entrada estandar.
*/

#include <stdio.h>

int main() {

	int c = fgetc(stdin); // obtengo un byte desde stdin.
	printf("El byte ingresado: %c\n", c);
	return 0;
}


