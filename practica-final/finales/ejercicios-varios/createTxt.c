/*
 *      Algoritmo para crear un archivo de texto
 */


#include <stdio.h>

int main(int argc, char** argv)
{
	if (argc!=3)
		return 1;
	
	FILE* bin;
	bin = fopen(argv[1],"wt");
	if (!bin) {
		printf("Imposible crear archivo\n");
		return 1;
	}
	if (fputs(argv[2],bin)<0){
		printf("Error al copiar string al archivo");
		return 1;
	}
	
	fclose(bin);
	return 0;
}
