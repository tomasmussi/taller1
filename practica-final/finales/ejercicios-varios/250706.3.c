/*
 *      Ejercicio [3] final 25/07/06
 * 		Algoritmo ANSI C que reciba dos numeros a y b por consola y cree
 * 		un archivo x.bin con b caracteres a
 */


#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	int i=0;
	int limit;
	int letra;
	
	if (argc!=3)
		return 1;
	limit=atoi(argv[2]);
	/* tomo el codigo ascii del caracter */
	letra=atoi(argv[1]);
	
	FILE* bin;
	bin = fopen("x.bin","wb");
	if (!bin)
		return 1;
		
	while (i<limit) {
		fputc(letra,bin);
		i++;
	}
	
	fclose(bin);
	return 0;
}
