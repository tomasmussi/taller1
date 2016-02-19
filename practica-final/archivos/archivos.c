#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct persona {
	char nombre[21];
	int edad;
};

void escribir_estructura() {
	struct persona p1;
	struct persona p2;
	strncpy(p1.nombre, "Tomas Crack", 21);
	p1.edad = 24;
	strncpy(p2.nombre, "Edu Mussi", 21);
	p2.edad = 64;
	
	FILE *fp = fopen("estructura", "wb+");
	fwrite(p1.nombre, 21, 1, fp);
	char *buf = (char*)(&p1.edad);
	fwrite(buf, sizeof(int), 1, fp);
	fwrite(p2.nombre, 21, 1, fp);
	buf = (char*)(&p2.edad);
	fwrite(buf, sizeof(int), 1, fp);
	fclose(fp);
}

void leer_estructura() {
	FILE *fp = fopen("estructura", "rb");
	while (!feof(fp)) {
		char nombre[21];
		char bufe[sizeof(int)];
		int edad;
		fread(nombre, 21, 1, fp);
		fread(bufe, sizeof(int), 1, fp);
		char *b = (char*) &edad;
		for (int c = 0; c < sizeof(int); c++) {
			b[c] = bufe[c];
		}
		printf("Persona: %s\nEdad: %d\n\n", nombre, edad);
		if (edad < 30) {
			printf("JOVEN\n");
		}
	}
	fclose(fp);
}

void escribir_texto() {
	FILE *fp = NULL;
	fp = fopen("texto", "w+");
	char buff[255];
	for(int c = 0; c < 255; c++) {
		buff[c] = 'd';
	}
	buff[254] = '\0';
	fgets(buff, 255, stdin);
	for (int i = 0; i < 3; i++) {
		fwrite(buff, strlen(buff), 1, fp);
	}
	fclose(fp);
}

void leer_texto() {
	FILE *fp = NULL;
	fp = fopen("texto", "r");
	while (!feof(fp)) {
		char buff[5];
		fread(buff, 5, 1, fp);
		printf("%s", buff);
	}
	printf("\n\n\n");
	fclose(fp);
}

void escribir() {
	FILE *fp = NULL;
	fp = fopen("archivo", "w");
	if (fp == NULL) {
		fp = fopen("archivo", "w+");
	}
	if (fp == NULL) {
		printf("No se puede abrir el archivo para escribirlo.\n");
	}
	for (int i = 0; i < 100; i++) {
		char buff[sizeof(int)];
		sprintf(buff, "%d", i);
		printf("Se escribe: %s\n", buff);
		fwrite(buff, sizeof(int), 1, fp);
	}
	fclose(fp);
}


void leer() {
	FILE *fp = NULL;
	fp = fopen("archivo", "r");
	while (!feof(fp)) {
		char buff[sizeof(int)];
		fread(buff, sizeof(int), 1, fp);
		printf("El numero escrito en el archivo es: %s\n", buff);
	}
	fclose(fp);
}


int main(int argc, char *argv[]) {
	/*if (argc > 1) {
		leer();
	} else {
		escribir();
	}*/
	// escribir_texto();
	// leer_texto();
	escribir_estructura();
	leer_estructura();
	return 0;
}
