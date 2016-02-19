/*
 Ejercicio de Archivos del coloquio de Taller
 */

#include <stdio.h>

char buffer[9];
int place;

int esComment(FILE* read){
	int c;
	while (((c=fgetc(read))!=EOF)&&(place<=8)){
		buffer[place++]=c;
	}
	if (place==9){
		buffer[place]='\0';
		place=0;
		if (strcmp(buffer,"COMMENT>")==0)
			return 1;
		return 0;
	}
	buffer[place]='\0';
	place=0;
	return 0;
}

int esCierreComment(FILE* read){
	int c;
	while (((c=fgetc(read))!=EOF)&&(place<=9)){
		buffer[place++]=c;
	}
	if (place==10){
		buffer[place]='\0';
		place=0;
		if (strcmp(buffer,"/COMMENT>")==0)
			return 1;
		return 0;
	}
	buffer[place]='\0';
	place=0;
	return 0;
}

int main(int argc, char** argv)
{
	FILE	*read, *write;
	int c;
	int saltear = 0;
	place = 0;
	
	read=fopen("a.html","rt");
	write=fopen("a.html","r+t");
	
	while ((c=fgetc(read))!=EOF) {
		if (!saltear){
			if ((char)c=='<') {
				printf("%c",(char)c);
				if (esComment(read)){
					printf("Era un comentario\n");
					saltear=1;
				}
				else if (esCierreComment(read)) {
					printf("Cierra un comentario\n");
					saltear=0;
				}
				else {
					printf("Ni abre ni cierra comentario");
					printf("%s\n", buffer);
					fputs(buffer,write);
				}
			} else {
				printf("%c",(char)c);
				if (!saltear)
					fputc(c,read);
			}
		}
	}
	
	/* lleno de ceros */
	while (ftell(write)<ftell(read))
		fputc('0',write);
		
	fclose(read);
	fclose(write);
	
	return 0;
}
