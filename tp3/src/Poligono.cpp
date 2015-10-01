#include "Poligono.h"
#include "Coordenada.h"
#include <algorithm>
#include <list>
#include <vector>
#include <cmath>


Poligono::Poligono(const std::list<Coordenada>& coordenadas) {
	this->coordenadas = coordenadas;
}

double Poligono::area(){
	std::list<Coordenada> li;
	std::vector<Coordenada> vector;
	std::copy(coordenadas.begin(), coordenadas.end(),
			std::back_inserter(vector));
	double area = 0;
	size_t j = vector.size() - 1;
	for (size_t i = 0; i < vector.size(); i++){
		double longitud = (vector[j].getLongitud() + vector[i].getLongitud())
				* GRADO_LONGITUD_EN_METROS;
		double latitud = (vector[j].getLatitud() - vector[i].getLatitud())
				* GRADO_LATITUD_EN_METROS;
		area = area + (longitud * latitud);
		j = i;
	}
	area = area * 0.5;
	return std::abs(area);
}

bool Poligono::tienePunto(const Coordenada& punto){
	std::list<Coordenada> li;
	std::vector<Coordenada> vector;
	std::copy(coordenadas.begin(), coordenadas.end(), std::back_inserter(vector));

	int i = 0;
	int j = 0;
	int c = 0;
	int nvert = vector.size();

	for (i = 0, j = nvert - 1; i < nvert; j = i++){
		if (((vector[i].latitud > punto.latitud) !=
				(vector[j].latitud > punto.latitud))
				&& (punto.longitud < (
				(vector[j].longitud - vector[i].longitud) *
				(punto.latitud - vector[i].latitud) /
						(vector[j].latitud - vector[i].latitud)
						+ vector[i].longitud ))){
			c = !c;
		}
	}
	return c != 0;
}

