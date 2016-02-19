/*
 *Ejercicio [5] final 05/02/08    
 *Escriba un programa ANSI C que reciba por línea de comandos un
  número (en base decimal) y una base (entre 2 y 16) e imprima el
  número recibido en la base pedida.
 */


#include <stdio.h>
#include <stdlib.h>
static int limit = 0;

void convertirNumero(int* resultado, long int numero, int base){
	int aux;
	while ((numero/base)>0){
		resultado[limit]=numero%base;
		aux=numero/base;
		numero=numero/base;
		limit++;
	}
	resultado[limit]=numero;
}

int main(int argc, char** argv) {
	if (argc<3){
		printf("Faltan argumentos\n");
		return 1;
	}
	int res[256];
	long int numero = atol(argv[1]);
	int base = atoi(argv[2]);
	convertirNumero(res,numero,base);
	int i=0;
	for (i=limit; i>=0; i--) {
		if (base == 16 ) {
			switch (res[i]) {
				case 10:
					printf("A");
					break;
				case 11:
					printf("B");
					break;
				case 12:
					printf("C");
					break;
				case 13:
					printf("D");
					break;
				case 14:
					printf("E");
					break;
				case 15:
					printf("F");
					break;	
				default:
					printf("%d", res[i]);
					break;
			}
		} else
			printf("%d", res[i]);
	}
	printf("\n");
	
	return 0;
}
