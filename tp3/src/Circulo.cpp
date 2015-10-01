#include "Circulo.h"
#include <math.h>
#include "Constantes.h"

Circulo::Circulo(const Coordenada& centro, double radio) : centro(centro){
	this->radio = radio;
}

double Circulo::area(){
	return M_PI * radio * radio;
}

bool Circulo::tienePunto(const Coordenada& punto){
	double latCuadrado = pow((punto.latitud() - centro.latitud())
			* GRADO_LONGITUD_EN_METROS, 2.0);
	double longCuadrado = pow((punto.longitud() - centro.longitud())
			* GRADO_LATITUD_EN_METROS, 2.0);
	double radioCuadrado = pow(radio, 2.0);
	return (latCuadrado + longCuadrado) < radioCuadrado;
}

