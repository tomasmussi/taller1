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
	getline(is, entry);
	lista.push_back(atoi(entry.c_str()));
	return is;
}

int main(int argc, char** argv)
{
	if (argc<2) {
		cout << "Faltan parametros" << endl;
		return 1;
	}
	int cantidad=atoi(argv[1]);
	list<int> listaEnteros;
	
	while ((cantidad>0)&&(cin >> listaEnteros)) {
		cantidad--;
	}
	list<int>::iterator it;
	for (it=listaEnteros.begin(); it!=listaEnteros.end(); ++it)
			cout << *it << endl;
	
	return 0;
}
