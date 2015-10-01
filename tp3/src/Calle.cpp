#include "Calle.h"
#include "Constantes.h"

bool Calle::superficieEdificada(){
	return false;
}

bool Calle::superficieArbolada(){
	return false;
}

const char Calle::caracter(){
	return ' ';
}

size_t Calle::nivel(){
	return CAPA_CERO;
}
