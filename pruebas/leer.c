#include <stdio.h>



int main(void){
	FILE *leer = fopen("/home/tomas/Desktop/out", "rb");
	char variable;
	size_t retorno;
	retorno = fread(&variable, sizeof(char), 1, leer);
	printf("El entero es: %c\n", variable);
	printf("Lo que retorno fread: %zd\n", retorno);
	return 0;
}
