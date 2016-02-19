/*
6)

Escriba una aplicación ANSI C++ que tome dos strings por línea de comandos e imprima el primero sin la segunda ocurrencia (si existe) del segundo.
*/

#include <iostream>
#include <string>

#define OCURRENCIA 2

int main(int argc, char* argv[]) {
	if (argc != 3)
		return 1;

	std::string primero(argv[1]);
	std::string segundo(argv[2]);

	size_t pos = std::string::npos;
	int i = 0;
	do {
		pos = primero.find(segundo, pos+1);
		++i;
	} while (pos != std::string::npos && i < OCURRENCIA);
			
	if (pos != std::string::npos)
		primero.erase(pos, segundo.size());

	std::cout << primero << std::endl;

	return 0;
}

