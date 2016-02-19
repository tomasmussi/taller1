/*
 *      Ejercicio [9] coloquio 25/07/06
 * 		Declarar una clase Arreglo<T> que permita organizar una
 * 		coleccion de objetos T en un arreglo. Incluya constructor
 *		default, de copia, operador <<, =, [] e int.
 * 	    Compilar con:
 * 		g++ -o ej9 -g  -Wno-non-template-friend -ansi 250706.9.cpp
 */


#include <iostream>
#include "250706.9.h"
using namespace std;

int main(int argc, char** argv)
{
	Arreglo<int> arreglo;
	
	arreglo.agregar(10);
	arreglo.agregar(20);
	arreglo.agregar(30);
	
	cout << arreglo[0] << endl;
	cout << arreglo[1] << endl;
	cout << arreglo[2] << endl;
	
	Arreglo<int> arreglo2;
	arreglo2=arreglo;
	
	cout << arreglo2[0] << endl;
	cout << arreglo2[1] << endl;
	cout << arreglo2[2] << endl;
			
	Arreglo<int> arreglo3 = arreglo2+arreglo;
	
	cout << "Arreglo 3 [suma]: " << endl; 
	cout << arreglo3 << endl;
	
	
	return 0;
}
