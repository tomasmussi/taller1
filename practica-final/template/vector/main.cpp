#include <iostream>
#include <string>

#include "vector.h"

class A {
	public:
		A() {}
		~A() {}
};

void ints() {
	Vector<int> ints;
	ints.add(8);
	ints.add(23);
	ints.add(100);
	ints.add(400);
	for (int i = 0; i < 4; i++) {
		std::cout << ints[i] << std::endl;
	}
	std::cout << "fin ints" << std::endl;
}

// No funciona... tal vez sera por el manejo interno de strings.
void strings() {
	Vector<std::string> strings;
	strings.add("hola");
	strings.add("como");
	strings.add("te");
	strings.add("va");
	for (int i = 0; i < 4; i++) {
		std::cout << strings[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "fin strings" << std::endl;
}

void aas() {
	A a1;
	A a2;
	Vector<A> vec;
	vec.add(a1);
	vec.add(a2);
	std::cout << "fin as" << std::endl;
}

int main(void) {
	ints();
//	strings();	
	aas();
	return 0;
}
