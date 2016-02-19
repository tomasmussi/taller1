

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#define AMP '&'

int main(void) {
	FILE *read = fopen("palabras.txt", "rt");
	FILE *write = fopen("palabras.txt", "r+t");

	while (! feof(read)) {
		int c = fgetc(read);
		if (c == '*') {
			int aux = fgetc(read);
			if (aux == '*') {
				fputc(AMP, write);
			} else {
				fputc((char)c, write);
				fputc((char)aux, write);
			}
		} else {
			fputc((char)c, write);
		}
	}
	long off = ftell(write);
	ftruncate(fileno(write), off);

	fclose(read);
	fclose(write);
	return 0;
}


