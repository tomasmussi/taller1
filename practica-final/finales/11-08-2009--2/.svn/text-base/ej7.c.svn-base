/* 7)
Escriba un programa ANSI C que procese el archivo datos.bin. El procesamiento
 consiste en reemplazar las secuencias de bytes 0x2F,0x31,0x3A por 0x31,0x3A.
 Adicionalmente, las búsquedas deben reiniciarse 3 bytes antes del último byte
 reemplazado. */

#include <stdlib.h>
#include <stdio.h>

#define LEN 3
#define LEN_REEMPL 2

static char* patron = {0x2F, 0x31, 0x3A};
static char* reemplazo = {0x31, 0x3A};

// funcin que busca el match con el patron
bool hayMatch(char* buffer) {
	bool comparacion = true;
	int pos = 0;
	while (comparacion && pos < LEN) {
		comparacion = (*(patron + pos) == *(buffer + pos));
		pos++;
	}
	return comparacion;
}

// funcion que realiza el reemplazo en el texto
void reemplazar(FILE* archivo) {
	fseek(archivo, -LEN, SEEK_CUR);
	fwrite(reemplazo, sizeof(char), LEN_REEMPL, archivo);
	fseek(archivo, -LEN, SEEK_CUR);
}

int main(int argc, char** argv) {
	// abro el archivo
	FILE* archivo = fopen("datos.bin", "rb+");
	if (!archivo)
		return 1;
	bool termine = false;
	char buffer[LEN];
	// mientras no haya terminado de procesar
	while (!termine) {
		// leo del archivo el tamaño del patron
		fread(buffer, sizeof(char), LEN, archivo);
		// si hay match
		if (hayMatch(buffer)) {
			// reemplazo y continuo leyendo
			reemplazar(archivo);
		} else {
			fseek(archivo, -LEN + 1, SEEK_CUR);
		}
		termine = feof(archivo);
	}
	fclose(archivo);
	return 0;
}
