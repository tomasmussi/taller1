
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void print_test(char *texto, bool test);
int busqueda_binaria(int* vector, int tamanio, int inicio, int fin, int valor);
int llamar(int *vector, int tamanio, int valor);
void pruebas(int *vector, int tamanio);

void print_test(char *texto, bool test){
	printf("%s: %s\n", texto, test ? "OK" : "ERROR");
}


int busqueda_binaria(int* vector, int tamanio, int inicio, int fin, int valor){
	static int cuenta = 0;
	cuenta++;
	if (cuenta < 40){
		//printf("%d ==> %d \n", inicio, fin);
	}
	if (inicio > fin){
		return -1;
	}
	int medio = ((inicio + fin)/2);
	if (cuenta < 40){
		/*printf("inicio + fin div 2: %d\n", ((inicio + fin)/2));
		printf("Medio: %d\n", medio);*/
	}
	if (vector[medio] == valor){
		return medio;
	} else if (vector[medio] > valor){
		return busqueda_binaria(vector, tamanio, inicio, medio - 1, valor);
	} else {
		return busqueda_binaria(vector, tamanio, medio + 1, fin, valor);
	}
}

int llamar(int *vector, int tamanio, int valor){
	return busqueda_binaria(vector, tamanio, 0, tamanio -1, valor);
}

void pruebas(int *vector, int tamanio){
	clock_t start, end;
	double cpu_time_used;
	start = clock();
	print_test("Elemento -1 no esta en el vector: ", llamar(vector,tamanio, -1) == -1);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Tardo: %.10f\n", cpu_time_used);
	start = clock();
	print_test("Elemento del medio esta en el vector: ", llamar(vector,tamanio, 5000) == 5000);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Tardo: %.10f\n", cpu_time_used);
	
	start = clock();
	print_test("Elemento 7500 esta", llamar(vector,tamanio, 7500) == 7500);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Tardo: %.10f\n", cpu_time_used);
}


int main(int argc, char *argv[]){
	
	int tamanio = 1000000000;
	if (argc == 2)
		tamanio = atoi(argv[1]);
	
	int vector[tamanio];
	for (int i = 0; i < tamanio; i++){
		vector[i] = i;
	}
	pruebas(vector, tamanio);	
	return 0;
}
