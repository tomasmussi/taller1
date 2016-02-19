/*
 *     Ejercicio [1] final 01/08/06
 *     Escribir un algoritmo que procese el archivo x.dat invirtiendo
 * 	   los bytes x y por y x
 */



#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[]) {

	FILE *read,*write;
	int caux=0;
	int c=0;
	int dobleX = 0;
	
	read=fopen("a.bin","rb");
	write=fopen("a.bin","r+b");
	c=fgetc(read);
	while (c!=EOF) {
		if (c=='x') {
			caux=c;
			if ((c=fgetc(read))!=EOF) {
				if (c=='y') {
					fputc('y',write);
					fputc('x',write);
					dobleX=0;
				} else {
					fputc(caux, write);
					if (c=='x'){
						dobleX=1;
					} else
						fputc(c,write);
				}
			}
		} else
			fputc(c, write);
		if (!dobleX)
			c=fgetc(read);
	}
	
	fclose(read);
	fclose(write);
	return 0;
}
