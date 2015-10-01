#include "Poligono.h"
#include "Coordenada.h"
#include <algorithm>
#include <list>
#include <vector>
#include <cmath>
#include <iostream>

#define INF 100000

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

/*
bool Poligono::tienePunto(Coordenada punto){
	//std::cout << "comienzo\n";
	// Paso 1. Centro poligono
	double lat = 0;
	double lon = 0;
	for (std::list<Coordenada>::iterator it = coordenadas.begin(); it != coordenadas.end(); it++){
		lat += it->getLatitud();
		lon += it->getLongitud();
	}
	size_t cantidad = coordenadas.size();
	Coordenada centroPoligono(lon / cantidad, lat / cantidad);
	//Paso 1 bis. Si el centro es igual al punto. RETURN TRUE
	if (centroPoligono == punto){
		std::cout << "Son lo mismo\n";
		return true;
	}

	if (punto.getLatitud() == centroPoligono.getLatitud()){
		// Mismo y, tengo que verificar que el punto.x este entre los extremos
		bool primero = true;
		double min = 0, max = 0;
		for (std::list<Coordenada>::iterator it = coordenadas.begin(); it != coordenadas.end(); it++){
			if (primero){
				min = it->getLongitud();
				max = it->getLongitud();
				primero = false;
			} else {
				if (it->getLongitud() > max){
					max = it->getLongitud();
				} else if (it->getLongitud() < min){
					min = it->getLongitud();
				}
			}
		}
		return min <= punto.getLongitud() && punto.getLongitud() <= max;
	}
	if (punto.getLongitud() == centroPoligono.getLongitud()){
		// Mismo x, tengo que verificar que el punto.y este entre los extremos
		bool primero = true;
		double min = 0, max = 0;
		for (std::list<Coordenada>::iterator it = coordenadas.begin(); it != coordenadas.end(); it++){
			if (primero){
				min = it->getLatitud();
				max = it->getLatitud();
				primero = false;
			} else {
				if (it->getLatitud() > max){
					max = it->getLatitud();
				} else if (it->getLatitud() < min){
					min = it->getLatitud();
				}
			}
		}
		return min <= punto.getLatitud() && punto.getLatitud() <= max;
	}
	//Sacar pendiente y recta entre dos puntos se esta repitiendo...

	//Paso 2. Recta entre centro poligono y punto a evaluar.
	double pendienteCentroPunto = (punto.getLatitud() - centroPoligono.getLatitud()) / (punto.getLongitud() - centroPoligono.getLongitud());
	double ordenadaCentroPunto = punto.getLatitud() - pendienteCentroPunto * punto.getLongitud();

	std::list<Coordenada> li;
	std::vector<Coordenada> vector;
	std::copy(coordenadas.begin(), coordenadas.end(),
			std::back_inserter(vector));
	for (size_t i = 0; i <= vector.size(); i++){
		//Paso 3. Sacar pendiente y ordenada entre 2 puntos de rectas.
		size_t actual = i % vector.size();
		size_t otro = (i + 1) % vector.size();
		if (vector[actual].getLongitud() == vector[otro].getLongitud()){
			if ((punto.getLongitud() - vector[actual].getLongitud()) * (punto.getLongitud() - centroPoligono.getLongitud()) > 0){
				return false;
			}
		} else {
			double pendiente = (vector[actual].getLatitud() - vector[otro].getLatitud()) / (vector[actual].getLongitud() - vector[otro].getLongitud());
			double ordenada = (vector[actual].getLatitud() - pendiente * vector[actual].getLongitud());
			// Paso 4. Obtener (longitud, latitud) a partir de interseccion de rectas.
			if (pendiente != pendienteCentroPunto){
				double longitud = (ordenada - ordenadaCentroPunto) / (pendienteCentroPunto - pendiente);
				double latitud = pendienteCentroPunto * longitud + ordenadaCentroPunto;
				Coordenada interseccion(longitud, latitud);
				//std::cout << "Comparando " << centroPoligono << "; " << punto << "\nCon " << centroPoligono << "; " << interseccion << std::endl;
				if (centroPoligono.distanciaCon(punto) > centroPoligono.distanciaCon(interseccion)){
					return false;
				}
			} else {
				return true;
			}
		}
	}
	return true;
}
*/

/*
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
*/


int pnpoly(int nvert, double *vertx, double *verty, double testx, double testy)
{
  int i, j, c = 0;
  for (i = 0, j = nvert-1; i < nvert; j = i++) {
    if ( ((verty[i]>testy) != (verty[j]>testy)) &&
	 (testx < (vertx[j]-vertx[i]) * (testy-verty[i]) / (verty[j]-verty[i]) + vertx[i]) )
       c = !c;
  }
  return c;
}


// Este es de la implementacion de stack overflow de Java
bool Poligono::tienePunto(Coordenada punto){
	std::list<Coordenada> li;
	std::vector<Coordenada> vector;
	std::copy(coordenadas.begin(), coordenadas.end(), std::back_inserter(vector));

	int i = 0;
	int j = 0;
	int c = 0;
	int nvert = vector.size();

	for (i = 0, j = nvert - 1; i < nvert; j = i++){
		if (((vector[i].latitud > punto.latitud) != (vector[j].latitud > punto.latitud))
				&& (punto.longitud < ((vector[j].longitud - vector[i].longitud) *
						(punto.latitud - vector[i].latitud) / (vector[j].latitud - vector[i].latitud) + vector[i].longitud ))){
			c = !c;
		}
	}
	return c != 0;
}


bool Poligono::superficieEdificada(){
	return false;
}
bool Poligono::superficieArbolada(){
	return false;
}
const char Poligono::caracter(){
	return 'p';
}
size_t Poligono::nivel(){
	return 0;
}

