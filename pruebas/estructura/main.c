#include <stdio.h>
#include "persona.h"

int main(void){
	per_t *persona = crear();
	imprimir(persona);

	char* v;
	v = (char*) persona;
	
	/*for (int i = 0; i < 8; i++)
		*(v + i) = 'a';
	*(v + 7) = '\0';*/
	*v = 'A';
	*(v + 1) = 'x';
	*(v + 2) = 'e';
	*(v + 3) = 'l';
	*(v + 4) = '\0';

	*(v + 8) = 0x1E;
	*(v + 9) = 0x00;
	*(v + 10) = 0x00;
	*(v + 11) = 0x00;

	imprimir(persona);
	destruir(persona);
	return 0;
}


