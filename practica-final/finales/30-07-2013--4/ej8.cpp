/**
Declare la clase Número para almacenar un número de 100 cifras decimales. 
Incluya: constructor default, constructor de copia, los operadores +, ++ (posfijo), ++ (prefijo), >, =, 
<< (corrimiento de bits) y <<(impresión). 
Implemente el operador <<(impresión).
*/

#include <iostream>

class Numero {
public:
	Numero() {
		std::cout << "default\n";
	}
	Numero(const Numero &otro) {
		std::cout << "copia\n";
	}
	Numero operator+(const Numero &otro) {
		std::cout << "operador + \n";
		return Numero();
	}

	Numero& operator++() {
		std::cout << "pre incremento\n";
		return *this;
	}

	Numero operator++(int) {
		std::cout << "post incremento\n";
		Numero tmp(*this);
		operator++();
		return tmp;
	}

	bool operator>(const Numero &otro) {
		std::cout << "a > b\n";
		return true;
	}

	Numero operator=(const Numero &otro) {
		return Numero();
	}

	short operator<<(int c) {
		std::cout << "Corrimiento de " << c << " bits\n";
		return 0;
	}

	friend std::ostream& operator<<(std::ostream &os, const Numero& numero) {
		os << "sobrecargado el operador impresion";
		return os;
	}

	friend std::istream& operator>>(std::istream& in, Numero &num) {
		int n;
		std::cout << "Dame num: ";
		in >> n;
		std::cout << "escribiste: " << n << std::endl;
		return in;
	}
};

int main(int argc, char *argv[]) {
	Numero a;
	Numero b(a);
	Numero c = a + b;
	a++;
	++a;
	c > a;
	std::cout << a;
	std::cin >> a;
	return 0;
}
