#include "Poligono.h"
#include "Coordenada.h"
#include <algorithm>
#include <list>
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

// Este es la implementacion copiada de python
bool Poligono::tienePunto(Coordenada punto){
	std::list<Coordenada> li;
	std::vector<Coordenada> vector;
	std::copy(coordenadas.begin(), coordenadas.end(),
			std::back_inserter(vector));
	int anterior = 2;
	for (size_t i = 0; i < vector.size(); i++){
		Coordenada a = vector[i % vector.size()];
		Coordenada b = vector[(i + 1) % vector.size()];

		Coordenada segmento = this->v_sub(b, a);
		Coordenada affine_point = this->v_sub(punto, a);
		int lado = this->getSide(segmento, affine_point);
		if (lado == 0){
			return false;
		} else if (anterior == 2){
			anterior = lado;
		} else if (anterior != lado){
			return false;
		}
	}
	return true;
}

Coordenada Poligono::v_sub(Coordenada a, Coordenada b){
	return Coordenada(a.getLongitud() - b.getLongitud(),
			a.getLatitud() - b.getLatitud());
}

int Poligono::getSide(Coordenada a, Coordenada b){
	double producto = this->producto(a, b);
	if (producto < 0){
		return -1;
	} else if (producto > 0){
		return 1;
	} else {
		return 0;
	}
}

double Poligono::producto(Coordenada a, Coordenada b){
	return a.getLongitud() * b.getLatitud() - a.getLatitud() * b.getLongitud();
}

/*
// Este es de la implementacion de stack overflow de Java
bool Poligono::tienePunto(Coordenada punto){
	std::list<Coordenada> li;
	std::vector<Coordenada> vector;
	std::copy(coordenadas.begin(), coordenadas.end(), std::back_inserter(vector));
	bool adentro = false;
	size_t i = 0, j = 0;
	for (i = 0, j = vector.size() - 1; i < vector.size(); j = i++){
		if ((vector[i].getLatitud() > punto.getLatitud()) != (vector[j].getLatitud() > punto.getLatitud())
				&& (punto.getLongitud() <
						(vector[j].getLongitud() - vector[i].getLongitud())
						* (punto.getLatitud() - vector[i].getLatitud())
						/ (vector[j].getLatitud() - vector[i].getLatitud() + vector[i].getLongitud()))){
			adentro = !adentro;
		}
	}
	return adentro;
}*/

