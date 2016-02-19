/*
 *    Ejercicio [4] final 19/02/08  
 * 	  Escribir un programa ANSI C no recursivo que admita una cadena
      de dígitos por línea de comandos e imprima todos los elementos
      de la serie de fibonacci menores que la cifra especificada.
 *      
 */


#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	
	if (argc<2) {
		printf("Argumentos incorrectos\n·");
		return 1;
	}
	long int numero=atol(argv[1]);
	int anterior=1;
	int actual=1;
	int aux=0;
	
	if (numero>1) {
		printf("%d ", anterior);
		printf("%d ", actual);
	} 
	aux=actual+anterior;
	while (numero>aux){
		printf("%d ", aux);
		anterior=actual;
		actual=aux;
		aux=actual+anterior;
	}
	printf("\n");	
	return 0;
}
