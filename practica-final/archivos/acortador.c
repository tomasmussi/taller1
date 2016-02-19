
/*
5)
Escribir un programa C que, sin crear archivos intermedios, procese el archivo “enteros.dat”. 
El procesamiento consiste en leer grupos de 2 enteros sin signo de 32 bits desde el archivo y escribir, 
en su lugar, la resta del grupo (es decir que el archivo se acortará).

Compilar con: gcc -ansi -std=gnu99 -o cortador acortador.c
*/

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>


#define TAM sizeof(int)

int toNum(char *buff) {
	int *i = (int*) buff;
	return *i;
}

void escribir(int numeros) {
	FILE *fp = fopen("numeros.dat", "w+b");
	for (int i = 0; i < numeros; i++) {
		char *c = (char*) &i;
		fwrite(c, sizeof(int), 1, fp);
	}
	fclose(fp);	
}

void leer() {
	FILE *fp = fopen("numeros.dat", "rb");
	while (! feof(fp)) {
		char buf[TAM];
		fread(buf, TAM, 1, fp);
		int *i = (int*) buf;
		printf("Numero: %d\n", *i);
	}
	fclose(fp);
}

void transformar() {
	FILE *read = fopen("numeros.dat", "rb");
	FILE *write = fopen("numeros.dat", "r+b");
	
	while (!feof(read)) {
		char buf1[TAM];
		char buf2[TAM];
		fread(buf1, TAM, 1, read);
		fread(buf2, TAM, 1, read);
		int n1 = toNum(buf1);
		int n2 = toNum(buf2);
		int c = n2 - n1;
		printf("Restando: %d - %d\n", n2, n1);
		char *buf3 = (char*) &c;
		fwrite(buf3, TAM, 1, write);
	}
	ftruncate(fileno(write), ftell(write));
	fclose(read);
	fclose(write);
}

int main(int argc, char *argv[]) {
	if (argc > 1) {
		int numeros = atoi(argv[1]);
		if (numeros % 2 != 0) {
			printf("Necesito cantidad par de numeros\n");
			return 1;
		}
		escribir(numeros);		
	} else {
		transformar();
	}
	leer();
}
