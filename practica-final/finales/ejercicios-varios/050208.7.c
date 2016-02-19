/*
 * Ejercicio [7] final 05/02/08  
 * Escriba una macro DONDE que imprima por salida standard el nombre
     del archivo fuente y la línea donde fue utilizada.
 */


#include <stdio.h>
#define DONDE printf("Archivo %s - Linea %d \n", __FILE__, __LINE__);

int main(int argc, char** argv)
{
	printf("Este es una mini aplicacion\n");
	printf("De prueba. Que mostrara que aca,\n");
	printf("En la siguiente linea se llamo a una macro:\n");
	DONDE;
	
	return 0;
}
