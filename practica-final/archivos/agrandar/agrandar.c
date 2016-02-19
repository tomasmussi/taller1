
/*
Escribir un programa C que procese el archivo texto.txt sobre sí mismo. 
* El proceso consiste en triplicar las palabras que tengan todas las vocales.
* */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAX 300
#define BUF_SIZE 10

bool vocales(const char *buffer, int tam) {
	int vocales[5];
	vocales[0] = vocales[1] = vocales[2] = vocales[3] = vocales[4] = 0;
	for (int i = 0; i < tam; i++) {
		switch(buffer[i]) {
			case 'a':
				vocales[0] = true;
				break;
			case 'e':
				vocales[1] = true;
				break;
			case 'i':
				vocales[2] = true;
				break;
			case 'o':
				vocales[3] = true;
				break;
			case 'u':
				vocales[4] = true;
				break;
		};
	}
	return vocales[0] && vocales[1] && vocales[2] && vocales[3] && vocales[4];
}

long reemplazar(FILE *fp, const char *palabra, int tam) {
	long donde = ftell(fp);
	FILE *write = fopen("texto.txt", "r+");
	fseek(write, donde, SEEK_SET);
	char *buffer = (char*) malloc(BUF_SIZE * tam * sizeof(char));
	memset(buffer, 0, BUF_SIZE * tam * sizeof(char));
	int indice = 0;
	int indice_write = 0;
	int escribir = 0;
	while (!feof(fp)) {
		int read = fgetc(fp);
		if (read != EOF) {
			buffer[indice % (BUF_SIZE * tam)] = (char) read;
			printf("%s\n", buffer);
			indice++;
		}
		if (escribir < tam) {
			fputc(palabra[escribir++], write);			
		} else if (escribir == tam) {
			fputc(' ', write);
		} else {
			fputc(buffer[indice_write % (BUF_SIZE * tam)], write);
			indice_write++;
		}
	}
	long tamanio_archivo = ftell(fp) + tam;
	while(tamanio_archivo > ftell(write)) {
		fputc(buffer[indice_write % (BUF_SIZE * tam)], write);
		indice_write++;
	}
	free(buffer);
	fclose(write);
	return donde;
}

int main(void) {
	FILE *fp = fopen("texto.txt", "r+");
	while (! feof(fp) && !finished) {
		char buffer[MAX];
		memset(buffer, 0, MAX);
		int indice = 0;
		int c = fgetc(fp);
		while (!feof(fp) && c != ' ') {
			buffer[indice++] = c;
			c = fgetc(fp);
		}
		if (vocales(buffer, indice)) {
			printf("vocales: %s\n", buffer);
			long donde = reemplazar(fp, buffer, indice);
			donde += 1;
			fseek(fp, donde, SEEK_SET);
		}
	}
	fclose(fp);
}
