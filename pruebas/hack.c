
#include <stdio.h>

typedef struct est{
	char buffer[3];
	int cookie;
} e_t;


int main(void){

	e_t e;
	e.cookie = 0;
	gets(e.buffer);

	if (e.cookie == 0x41){
		printf("Ganaste\n");
	} else {
		printf("Perdiste\n");
	}
	/*printf("Comienzo c:\t %p\n", e.buffer);
	printf("Siguiente: \t %p\n", e.buffer + 1);
	printf("Comeinzo cookie: %p\n", (void*)& (e.cookie));

	printf("Que pasa si quiero ver que tiene e.buffer: %s\n", e.buffer);
	printf("char: %c\n", e.buffer[5]);
	if (e.buffer[5] == '\0'){
		printf("SEEEE\n");
		printf("dir: %p\n", &(e.buffer[5]));
	}
	printf("Cookie tiene: %d\n", e.cookie);*/
	return 0;
}
