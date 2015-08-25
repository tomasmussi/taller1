

#include <stdio.h>

int main(void){
	char *nombre = "/home/tomas/Desktop/out";
	FILE *out = fopen(nombre, "wb");
	if (out == NULL){
		printf("Error al abrir el archivo\n");
		return 1;
	}
	char variable = 0x41;
	//fread(&variable, sizeof(char), 1, stdin);
	fwrite(&variable, sizeof(char), 1, out);
	fclose(out);
	return 0;
}
	
