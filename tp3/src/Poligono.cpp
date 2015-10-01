#include "Poligono.h"
#include "Coordenada.h"
#include <algorithm>
#include <list>
#include <vector>
#include <cmath>


Poligono::Poligono(const std::list<Coordenada>& coordenadas) {
	std::list<Coordenada> li;
	std::copy(coordenadas.begin(), coordenadas.end(), std::back_inserter(vector));
}

double Poligono::area(){
	double area = 0;
	size_t j = vector.size() - 1;
	for (size_t i = 0; i < vector.size(); i++){
		double longitud = (vector[j].longitud() + vector[i].longitud())
				* GRADO_LONGITUD_EN_METROS;
		double latitud = (vector[j].latitud() - vector[i].latitud())
				* GRADO_LATITUD_EN_METROS;
		area = area + (longitud * latitud);
		j = i;
	}
	area = area * 0.5;
	return std::abs(area);
}

bool Poligono::tienePunto(const Coordenada& punto){
	int i = 0;
	int j = 0;
	int c = 0;
	int nvert = vector.size();
	for (i = 0, j = nvert - 1; i < nvert; j = i++){
		bool condicion1 = (vector[i].latitud() > punto.latitud()) !=
				(vector[j].latitud() > punto.latitud());
		double resultado =  (vector[j].longitud() - vector[i].longitud()) *
				(punto.latitud() - vector[i].latitud()) /
				(vector[j].latitud() - vector[i].latitud())
				+ vector[i].longitud();
		bool condicion2 = punto.longitud() < resultado;

		if (condicion1 && condicion2){
			c = !c;
		}
	}
	return c;
}

