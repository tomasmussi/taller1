/*
5)
¿Qué es un parámetro opcional en C++?¿Cómo se utiliza?¿Dónde puede usarse? Ejemplifique.

Un parametro opcional permite que si no se especifica dicho parametro, se utilizara un valor por default.
Puede especificarse en cualquier funcion, metodo, etc.
Hay que tener cuidado con dejar expuestas ambigüedades por la posible sobrecarga de metodos.

cuidado de tener:

void funcion(int a);
void funcion(int a, char b = 'c');

A cual llamo?

*/

#include <iostream>

void funcion (int a, int b = 30) {
	std::cout << a << " y " << b << std::endl;
}


int main(void) {
	funcion(10);
	funcion(10, 100);
	return 0;
}
