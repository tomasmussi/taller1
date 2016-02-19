/*
 *    Ejercicio [6] final 19/02/08
 *    Defina el operador » de forma que cargue el contenido de una
      lista de STL. La carga se iniciará con el ingreso del número
      de elementos a ingresar. (Suponer que la clase contenida en la
      lista implementa el operador » ).
 */


#include <iostream>
#include <list>
#include <cstdlib>
using namespace std;

istream& operator>>(istream& is, list<int>& lista) {
	string entry;
	getline(entry, is);
	lista.push_back(atoi(entry.c_str());
	return is;
}

int main(int argc, char** argv)
{
	int cantidad=0;
	list<int> listaEnteros;
	cout << "Cantidad de elementos a cargar en la lista?:  " << endl;
	cin >> cantidad;
	cout << "Ingrese los valores.-" << endl;
	
	while (cantidad){
		cin >> listaEnteros;
		cantidad--;
	}
	
	return 0;
}
