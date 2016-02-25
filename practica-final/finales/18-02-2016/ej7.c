/**
 * 7) Escriba un programa ISO C que reciba por linea de comando una UNICA cadena
 * de la forma "HHHH x HHHH" donde "x" es una operacion (+, -, *, /) y
 * "HHHH" es un numero hexadecimal de 4 simbolos.
 * El programa debe imprimir el resultado de la operacion aritmetica indicada en formato
 * decimal.
 * Por ejemplo: calc.exe "000A + 0002" => 12
 * 
 * Compilar: gcc -ansi -std=c99 -o prueba ej7.c
 * 
 * No se pidio validar nada en particular
 * */

#include <stdio.h>
#include <math.h>

int parsear(int *a, int *b, char *op, const char *arg);
int hexa_a_dec(const char *arg, int start, int end);
int pot(int base, int exp);


int main(int argc, char *argv[]) {
	int a,b;
	char op;
	parsear(&a, &b, &op, argv[1]);
	int res;
	switch(op) {
		'+' : 
			res = a + b; break;
		'-' : 
			res = a - b; break;
		'*' : 
			res = a * b; break;
		'/' : 
			res = a / b; break;
	};
	printf("%d\n", res);
	return 0;
}


int parsear(int *a, int *b, char *op, const char *arg) {
	// "000A + 0002"
	// "012345678910"
	*a = hexa_a_dec(arg, 0, 3);
	*b = hexa_a_dec(arg, 7, 10);
	*c = arg[5];
}

int hexa_a_dec(const char *arg, int start, int end) {
	int res = 0;
	for (int i = start; i <= end; i++) {
		char caracter = arg[i] - '0';
		char digito = caracter * pot(16, end - i);
		res += digito;
	}
	return res;
}

int pot(int base, int exp) {
	return pow(base, exp);
}
