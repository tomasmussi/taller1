/*
 *     Ejercicio [5] final 12/12/06
 *     Escribir un algoritmo ANSI C que, sin crear archivos intermedios
 * 	   altere el archivo a.txt reemplazando la secuencia '//' por '*'
 * 	   Excepto si se encuentra entre parentesis	
 */



#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[]) {

	FILE *read,*write;
	int c=0;
	int caux=0;
	int dobleBarra = 0;
	int parentesis = 0;
	
	read=fopen("a.txt","rt");
	write=fopen("a.txt","r+t");
	
	while ((c=fgetc(read))!=EOF){
		if (c=='(')
			parentesis = 1;
		if (c==')')
			parentesis = 0;	
		if (c=='/') {
			caux=c;
			c=fgetc(read);
			if (c!=EOF){
				if ((c=='/')&&(!parentesis)){
					fputc('*',write);
					dobleBarra=1;
				}
				else {
					fputc((char)caux,write);
					dobleBarra = 0;
				}
			} else {
				c=caux;
				dobleBarra = 0;
			}
		}
		if (c!=EOF)
			if ((c!='/')||((c=='/')&&(!dobleBarra)))
				fputc((char)c,write);
	}
	
	/* si queda basura al final del archivo completo con 0 */
	while (ftell(write)<ftell(read))
		fputc('0',write);
	
	fclose(read);
	fclose(write);
	return 0;
}
