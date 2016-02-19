/*
 *     Ejercicio [3] final 11/07/06
 *     Escribir un algoritmo ANSI C que, sin crear archivos intermedios
 * 	   altere el archivo a.bin reemplazando la secuencia ab por abc
 */


#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	FILE* binFile = NULL;
	int* buffer = NULL;
	int byte = 0;
	int index = 0;
	int tam = 0;
	int tam2 = 0;
	int result = 0;
	
	if (argc!=2)
		return 1;
	
	binFile=fopen(argv[1],"r+b");
	if (!binFile)
		return 1;
	
	/* calculo el tamanio del archivo */
	if (fseek(binFile,0L,SEEK_END)!=0)
		return 1;
	tam = ftell(binFile);
	if (tam==-1) {
		return 1;
	}
	tam2 = (tam)*(sizeof(int));
	buffer = (int*)malloc(tam2);
	
	/* posiciono el file pointer al comienzo del archivo */
	if (fseek(binFile,0L,SEEK_SET) != 0)
		return 1;
	
	/* acumulo el contenido del archivo en el buffer */
	while ((byte = fgetc(binFile))!= EOF ) {
		buffer[index]=byte;
		index++;
	}
	
	/* posiciono el file pointer al comienzo del archivo */
	if (fseek(binFile,0L,SEEK_SET) != 0)
		return 1;
		
	/* analizo buffer y escribo en archivo */
	for (index=0; index<(tam2/4); index++){
		if (buffer[index]=='a'){
			result = fputc('a',binFile);
			index++;
			if (buffer[index]=='b'){
				result = fputc('b',binFile);
				result = fputc('c',binFile);
			} else index--;
		} else
			result = fputc((char)buffer[index],binFile);
	}
	fclose(binFile);
	free(buffer);
	return 0;
}
