#include "Poligono.h"
#include "Coordenada.h"
#include <vector>
#include <cmath>

Poligono::Poligono(std::list<Coordenada> coordenadas) {
	this->coordenadas = coordenadas;
}

Poligono::~Poligono() {
}

double Poligono::area(){
	std::list<Coordenada> li;
	std::vector<Coordenada> vector;
	std::copy(coordenadas.begin(), coordenadas.end(), std::back_inserter(vector));
	double area = 0;
	size_t j = vector.size() - 1;
	for (size_t i = 0; i < vector.size(); i++){
		double longitud = (vector[j].getLongitud() + vector[i].getLongitud()) * GRADO_LONGITUD_EN_METROS;
		double latitud = (vector[j].getLatitud() - vector[i].getLatitud()) * GRADO_LATITUD_EN_METROS;
		area = area + (longitud * latitud);
		j = i;
	}
	area = area * 0.5;
	return std::abs(area);
}


bool Poligono::tienePunto(Coordenada punto){
	return true;
}

