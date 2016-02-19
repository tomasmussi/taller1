#include "Test.h"
#include <iostream>

Test::Test() {
	std::cout << "Se construye un Test\n";
}

Test::~Test() {
	std::cout << "Se destruye un Test\n";
}

Test::Test(const Test &other) {
	std::cout << "Se construye un Test a partir de otro\n";
	std::cout << "3\n";
}


Test Test::operator=(const Test &test) {
	std::cout << "4\n";
	return Test();
}

bool Test::operator>(const Test &other) {
	std::cout << "1\n";
	return true;
}

Test::operator float() {
	std::cout << "2/4\n";
	return 1.0;
}

Test Test::operator=(float as) {
	std::cout << "5\n";
	return Test();
}

