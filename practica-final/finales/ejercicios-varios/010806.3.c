/*
 *	Ejercicio [3] Final 01/08/2006 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	int i=0;
	int index=0;
	if (argc<3) {
		printf("Argumentos incorrectos\n");
		return 1;
	}
	
	char* str1 = argv[1];
	char* str2 = argv[2];
	char* find=strstr(str1,str2);
	char* aux=(char*)malloc(strlen(str1)+1);
	
	while (find!=NULL) {
		while (str1!=find){
			aux[index]=str1[i];
			str1++;
			index++;
		}
		i+=strlen(str2);
		while (i<strlen(str1)){
			aux[index]=str1[i];
			i++;
			index++;
		}
		aux[index]='\0';
		str1=aux;
		find=strstr(str1,str2);
		index=0;
		i=0;
	}
	printf("Cadena final: %s\n", str1);
	free(aux);
	return 0;
}
