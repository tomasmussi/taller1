#include <stdio.h>
#include "otro.h"

extern int i;

int main(void) {
	printf("El valor de i: %d\n", i);
	incrementar_i();
	printf("El nuevo valor de i: %d\n", i);
	return 0;
}
