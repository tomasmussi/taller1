/**
 * 5) Defina el operador<< de forma que imprima los elementos de una lista
 * de STL de enteros ordenados de mayor a menor. Cabe destacar que la semantica
 * del operador debe respetar usos y costumbres de C++.
 * */

std::ostream operator<<(std::ostream &out, const std::list<int> &lista) {
	std::list<int> copia = std::copy(lista.begin(), lista.end()); // Creo que no es del todo asi el copy... Revisar
	copia.sort();
	
	std::list<int> it = copia.rbegin();
	// it es un iterador del fin al principio => mayor a menor
	
	while (it != copia.rend()) {
		out << (*it) << std::endl;
		it++;
	}
	return out;
}
