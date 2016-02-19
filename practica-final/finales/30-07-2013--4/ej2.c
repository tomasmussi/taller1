/*
 * 
 * Escriba un programa ISO C que procese el archivo de números datos.txt sobre sí mismo. 
 * El procesamiento consite en convertir los números encontrados (de 1 o más cifras decimales) a octal.
 * 
 * */

#include <stdio.h>




int main(int argc, char *argv[]) {
	
	FILE *fp = fopen("datos.txt", "r+t");


	fclose(fp);
}
