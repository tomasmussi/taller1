#include <iostream>

/*
8)

Declare una clase Ciudadano para encapsular el nombre, DNI y CUIT de una persona. Incluya al menos:
Constructor default,
Constructor con valores de inicialización y Constructor de Copia;
Operador <, ==, =, int y >> (carga desde STDIN).
Implemente el operador>>.
*/

class Ciudadano {

public:

	Ciudadano() : _nombre("Tomas"), _dni(36171385), _cuit("20361713851") {
	}

	Ciudadano(const std::string& nombre, long unsigned DNI, const std::string& CUIT)
		: _nombre(nombre), _dni(DNI), _cuit(CUIT) {
	}

	Ciudadano(const Ciudadano &otro) :
		_nombre(otro._nombre), _dni(otro._dni), _cuit(otro._cuit) {
	}

	bool operator<(const Ciudadano &other) const {
		return this->_dni > other._dni;
	}

	bool operator==(const Ciudadano &other) const {
		return this->_dni == other._dni;
	}

	Ciudadano operator=(const Ciudadano &other) {
		return Ciudadano(other);
	}

	operator int() {
		return (int) this->_dni;
	}

	friend std::istream& operator>>(std::istream& in, Ciudadano& obj) {
		in >> obj._nombre;
		in >> obj._dni;
		in >> obj._cuit;
		return in;
	}
	
	friend std::ostream& operator<<(std::ostream& out, const Ciudadano& obj) {
		out << obj._nombre << "\t" << obj._dni << "\t" << obj._cuit;
		return out;
	}

	~Ciudadano() {
	}

	const std::string& nombre() const {
		return this->_nombre;
	}

	const unsigned long dni() const {
		return this->_dni;
	}

private:
	std::string _nombre;
	unsigned long _dni;
	std::string _cuit;
};


int main(int argc, char *argv[]) {
	Ciudadano ci;
	Ciudadano otro = ci;
	std::cout << "Tengo a otro con: " << otro << std::endl;
	int i = ci;
	std::cout << "Casteado a int: " << i << std::endl;

	std::cout << "La prueba definitiva." << std::endl;
	std::cin >> ci;
	std::cout << "Tengo a ci con: " << ci << std::endl;

	return 0;
}

