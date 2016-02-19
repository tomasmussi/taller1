/*
 *     Ejercicio [2] final 190208
 * 	   Escriba un programa ANSI C que reciba por línea de comandos una
       cadena de la forma “x-mmmmmmmmmmmm|x-mmmmmmmmmm...” donde x es un
       dígito y mmmmmmmm un título de un menú. El programa debe borrar 
       la pantalla, desplegar el menú y devolver al SO el numero de 
       opcion elegida. Por ejemplo:

		menu.exe “1-Ejecutar|2- Salir del Sistema“
		debe borrar la pantalla, desplegar el menú:
		1-Ejecutar
		2-Salir del Sistema
		y devolver el número de opción elegida al SO. Cabe destacar que el 
		programa debe validar que la opción elegida por el usuario 
		sea válida.
 * 	   
 */


#include <stdio.h>

void clearScreen( ){
	printf("\x1b[2J");
	printf ("\x1b[H");
}

int main(int argc, char** argv) {
	
	char* pch;
	/* se acumulan hasta 20 opciones */
	char opciones[20];
	int nOpciones=0;
	int i=0;
	int opt=0;
	int opcionValida=0;
	
	if (argc<2) {
		printf("Argumentos incorrectos\n");
		return 1;
	}
	/* asumo que la cadena es correcta */
	char* menu=argv[1];
	/* borra la pantalla */
	clearScreen();
	/* */
	pch = strtok (menu,"|");
    while (pch != NULL) {
    	opciones[nOpciones]=pch[0];
    	nOpciones++;
		printf ("%s\n",pch);
		pch = strtok (NULL, "|");
	}
	
	while (!opcionValida){
		opt=getchar();
		if (opt!='\n'){
			for (i=0; i<nOpciones; i++) {
				if ((char)opt==opciones[i])
					opcionValida=1;
			}
			if (opcionValida)
				printf("Opcion valida: %c\n", opt);
			else {
				printf("Opcion Invalida: %c no existe!\n", opt);
				printf("\nOpciones disponibles: \n");
				printf("--------------------- \n");
				for (i=0; i<nOpciones; i++)
					printf("	%c\n",opciones[i]);
			}
		}
	}
	return 0;
}
