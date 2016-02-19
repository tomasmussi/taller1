#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

static int nums[] = {1,2,3,4};


int convertir(char *buff) {
	int i;
	char *b = (char*) &i;
	for (int c = 0; c < sizeof(int); c++) {
		b[c] = buff[c];
	}
	return i;
}

void escribir() {
	FILE *fp = fopen("multi", "w+b");
	if (fp == NULL) {
		printf("ERRNO: %d\n", errno);
		return;
	}
	for (int i = 0; i < 4; i++) {
		printf("Escribiendo desde: %p\n", (void*) &nums[i]);
		fwrite(&nums[i], sizeof(int), 1, fp);
	}
	fclose(fp);
}

void multiplicar() {
	FILE *fp = fopen("multi", "r");
	FILE *write = fopen("multi", "r+");
	while (! feof(fp)) {
		char buff[sizeof(int)];
		fread(buff, sizeof(int), 1, fp);
		int num = convertir(buff);
		num *= 2;
		char *c = (char*) &num;
		fwrite(c, sizeof(int), 1, write);
	}
	fclose(fp);
	fclose(write);
}

void leer() {
	FILE *fp = fopen("multi", "r");
	while (!feof(fp)) {
		char buff[sizeof(int)];
		fread(buff, sizeof(int), 1, fp);
		int n = convertir(buff);
		printf("%d\n", n);
	}
	fclose(fp);
	printf("\n\n\n");
}


int main(void) {
	escribir();
	leer();
	multiplicar();
	leer();
	return 0;
}
