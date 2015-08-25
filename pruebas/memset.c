#include <stdio.h>
#include <string.h>

typedef struct estr {
	int entero;
	char letra;
} estr_t;

void funcion(){
	unsigned char c = 0;
	for (c = 0; c <= 254; c++){
		printf("C: %d\n", c);
	}
}


int main(void){
	estr_t estructura;
	estr_t *puntero = memset(&estructura, 256, sizeof(estr_t));
	printf("Entero: %x\n", puntero->entero);
	printf("Letra: %x\n", puntero->letra);

	printf("Sizeof int: %d\n", sizeof(int));
	printf("Sizeof char: %d\n", sizeof(char));
	//funcion();
	return 0;
}
