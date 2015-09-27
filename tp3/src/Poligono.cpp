#include "Poligono.h"
#include "Coordenada.h"
#include <cmath>

Poligono::Poligono(std::list<Coordenada> coordenadas) {
	this->coordenadas = coordenadas;
}

Poligono::~Poligono() {
}

double Poligono::area(){
	std::list<Coordenada>::iterator anterior = coordenadas.begin();
	std::list<Coordenada>::iterator siguiente = coordenadas.begin();
	siguiente++;
	double area = 0;
	while (siguiente != coordenadas.end()){
		double xi = anterior->getLongitud() * GRADO_LONGITUD_EN_METROS;
		double yi_1 = siguiente->getLatitud() * GRADO_LATITUD_EN_METROS;
		double xi_1 = siguiente->getLongitud() * GRADO_LONGITUD_EN_METROS;
		double yi = anterior->getLatitud() * GRADO_LATITUD_EN_METROS;
		area += ((xi * yi_1) - (xi_1 * yi));
		anterior++;
		siguiente++;
	}
	double xn = coordenadas.end()->getLongitud() * GRADO_LONGITUD_EN_METROS;
	double y1 = coordenadas.begin()->getLatitud() * GRADO_LATITUD_EN_METROS;
	double x1 = coordenadas.begin()->getLongitud() * GRADO_LONGITUD_EN_METROS;
	double yn = coordenadas.end()->getLatitud() * GRADO_LATITUD_EN_METROS;
	area += ((xn * y1) - (x1 * yn));
	area = area * 0.5;
	return std::abs(area);
}

bool Poligono::tienePunto(Coordenada punto){
	return true;
}

/*
bool Poligono::colisionaCon(Figura otraFigura){
	return false;
}*/
