/*
 *     Ejercicio [3] final 11/07/06
 *     Escribir un algoritmo ANSI C que, sin crear archivos intermedios
 * 	   altere el archivo a.bin reemplazando la secuencia ab por abc
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char buffer[1024];
	int top;
	int bottom;
} tCola;

void cola_crear(tCola* cola) {
	cola->top=cola->bottom=0;
}

int cola_poner(tCola* cola,char c) {
	if ((1024+cola->top-cola->bottom)%1024==1023) 
		return -1; /* buffer lleno */
	cola->buffer[cola->top++]=c;
	if (cola->top==1024) cola->top=0;
	return 0;
}

char cola_sacar(tCola* cola) {
	char c;
	c=cola->buffer[cola->bottom++];
	if (cola->bottom==1024) cola->bottom=0;
	return c;
}

int cola_vacia(tCola* cola) {
	return cola->top==cola->bottom;
}

int main(int argc, char* argv[]) {

	FILE *read,*write;
	int c=0;
	char c2;
	tCola cola;
	int wasA = 0;
	int wasB = 0;
	int colaVacia = 0;
	/* creo cola buffer */
	cola_crear(&cola);
	
	read=fopen("a.bin","rb");
	write=fopen("a.bin","r+b");

	do {
		c=fgetc(read);
		if (c!=EOF) {
			if (cola_poner(&cola,(char)c)==-1)
				exit(1); /* no mas lugar */
			if ((char)c=='a')
				wasA=1;
			if ((char)c=='b')
				wasB=1;
			
		}
		if (!cola_vacia(&cola)) {
			c2=cola_sacar(&cola);
			if (cola_vacia(&cola)) /* verifico q no haya quedado vacia */
				if (c==EOF)
					colaVacia=1;
			fputc(c2,write);
			if ((wasA)&&(wasB)) {
				if (cola_poner(&cola,'c')==-1)
					exit(1); /* no mas lugar */
				wasA=0; wasB=0;
			}	
		} else colaVacia=1;
		
	} while (!colaVacia);
	
	fclose(read);
	fclose(write);
	return 0;
}
