#include "Circulo.h"
#include <math.h>

Circulo::Circulo(Coordenada centro, double radio){
	this->centro = centro;
	this->radio = radio;
}

Circulo::~Circulo() {
}

double Circulo::area(){
	return M_PI * radio * radio;
}

bool Circulo::tienePunto(Coordenada punto){
	double latCuadrado = pow((punto.getLatitud() - centro.getLatitud()), 2.0);
	double longCuadrado = pow((punto.getLongitud() - centro.getLongitud()), 2.0);
	double radioCuadrado = pow(radio, 2.0);
	return (latCuadrado + longCuadrado) < radioCuadrado;
}

