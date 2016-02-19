#include <cstdio>
#include <ctype.h>
#include <cstring>

bool isnumber(char* cadena) {
	bool ret = true;
	while (cadena && ret)
		ret = isdigit(cadena++);
	return ret;
}

int main(int argc, int argv) {
	if (argc != 4)
		return 1;
	if (!isnumber(argv[1]) || !isnumber(argv[2]) || !isnumber(argv[3]))
		return 2;
	long A = strtol(argv[1],0,10);
	if (A == 0) return 3;
	long B = strtol(argv[2],0,10);
	long Yi = strtol(argv[3],0,10);
	printf("El resultado es %f\n", (Yi - B)/ (float) A);
	return 0
}
