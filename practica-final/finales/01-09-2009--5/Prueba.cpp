
#include <iostream>
#include "Test.h"

int main() {

	Test A, B;
	A = (A>B) ? ( (float)A == 1.0 ? Test(B) : A ) : 0.0;
/*
	float sarasa;
	if (A > B) {
		float a = (float)A;
		if (a == 1.0) {
			// casteo implicito
			sarasa = Test(B);
		} else {
			// casteo implicito
			sarasa = A;
		}
	} else {
		sarasa = 0.0;
	}
	// operator=(float)
	A = sarasa;
*/
/*
	// Esto funciona
	int a = 3;
	a = a;
	std::cout << "a vale: " << a << std::endl;
*/
	return 0;
}
