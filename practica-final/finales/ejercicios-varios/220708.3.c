/*
 * Ejercicio [3] final 22/07/08      
 * Escribir un programa ANSI C que admita una cadena de 3 caracteres 
 * por línea de
   comandos e imprima los resultantes de todas las permutaciones 
   posibles.
*  Ej. MiPrograma ABC debe imprimir ABC, ACB, BAC, BCA, CAB, CBA.
 */


#include <stdio.h>
#include <string.h>

void imprimirChars(char* c, int i, int j, int k) {
	printf("%c%c%c\n",c[i],c[j],c[k]);
}

int main(int argc, char** argv)
{
	if (argc<2) {
		printf("Faltan argumentos\n");
		return 1;
	}
	int length=strlen(argv[1]);
	if (length!=3) {
		printf("La cadena debe tener 3 caracteres \n");
		return 1;
	}
	char* cadena = argv[1];
	int j=0;
	int i=0;
	int k=0;
	
	for (i=0; i<length; i++) {
		for (j=0; j<length; j++) {
			if (j==i) continue;
			for (k=0; k<length; k++) {
				if ((k==j)||(k==i)) continue;
				imprimirChars(cadena,i,j,k);
			}
		}
	}
	return 0;
}
