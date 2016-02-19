/*
7)
Escribir un programa ISO C que procese el archivo palabras.txt sobre sí mismo. 
El proceso consiste en duplicar las palabras que tengan más de 2 consonantes.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 30

char vacio = ' ';
int INIT = 300;

bool consonante(const char *palabra, int tam) {
	int cant = 0;
	for (int i = 0; i < tam; i++) {
		if (palabra[i] != 'a' && palabra[i] != 'e' && palabra[i] != 'i' && palabra[i] != 'o' && palabra[i] != 'u') {
			cant++;
		}
	}
	return cant > 2;
}

int leer(FILE *fp, int *buffer, int *indice, int *tam) {
	if (*indice < *tam) {		
		int r = buffer[*indice];
		(*indice)++;
		printf("Leo del buffer: %c\n", (char) r);
		return r;
	} else {
		if (*indice > 0) {
			*indice = 0;
			*tam = 0;
		}
		return fgetc(fp);
	}
}

void cargar_buffer(FILE *fp, int *buffer, int *indice, int *tam, int bytes) {
	
	char byte_buf[MAX];
	int t = 0;
	
	while(! feof(fp) && t < bytes) {
		int c = fgetc(fp);
		byte_buf[t] = (char) c;
		t++;
	}
	byte_buf[t] = '\0';
	printf("Tengo que leer %d bytes y se leyeron %d al final\n", bytes, t);
	printf("Cargo al buffer: %s\n", byte_buf);
	long off = -1 * bytes;
	printf("Vuelvo %ld\n", off);
	fseek(fp, off, SEEK_CUR);

	if (((*indice) + bytes) >= (*tam)) {
		INIT = INIT * 2;
		buffer = realloc(buffer, INIT);
	}
	int nuevo_indx = *indice;
	for (int i = 0; i < bytes; i++) {
		int c = (int) byte_buf[i];
		buffer[nuevo_indx] = c;
		nuevo_indx++;
	}
	*tam = *tam + bytes;
}

int main() {
	FILE *fp = fopen("palabras.txt", "r+t");
	int *aux = malloc(INIT * sizeof(int));
	int indice = 0;
	int tam = 0;
	
	while(! feof(fp)) {
		char palabra[MAX];
		int sub = 0;
		int c = leer(fp, aux, &indice, &tam);
		palabra[sub++] = c;
		while (! feof(fp) && c != vacio) {
			c = leer(fp, aux, &indice, &tam);
			palabra[sub++] = c;
		}
		palabra[sub] = '\0';
		printf("Tengo palabra: %s\n", palabra);
		if (consonante(palabra, sub)) {
			cargar_buffer(fp, aux, &indice, &tam, sub);
			fwrite(palabra, sub, 1, fp);
		}
		fwrite(palabra, sub, 1, fp);
	}
	
	fclose(fp);
	free(aux);
	return 0;
}

/*
int main() {
	FILE *fp = fopen("palabras.txt", "r+t");
	
	fseek(fp, 0, SEEK_END);
	int tam = ftell(fp);
	printf("Tamanio: %d\n", tam);
	int *buffer = (int*) malloc(tam * sizeof(int));

	fseek(fp, 0, SEEK_SET);
	int index = 0;
	while(! feof(fp)) {
		int c = fgetc(fp);
		buffer[index++] = c;
	}
	printf("Pasa el copiado\n");
	
	fseek(fp, 0, SEEK_SET);
	int i = 0;
	while(i < index) {
		char palabra[40];
		memset(palabra, 0, 40);
		int sub = 0;
		int c = buffer[i];
		while (i < index && c != ' ') {
			palabra[sub] = c;
			sub++;
			i++;
			c = buffer[i];
		}
		fwrite(palabra, sub, 1, fp);
		if (consonante(palabra, sub)) {
			fwrite(palabra, sub, 1, fp);
		}
		fwrite(&vacio, 1, 1, fp);
		i++;
	}
	
	
	fclose(fp);
	free(buffer);
	return 0;
}
*/



