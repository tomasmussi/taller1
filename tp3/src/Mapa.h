#ifndef MAPA_H_
#define MAPA_H_

#include "Coordenada.h"
#include "Figura.h"
#include "Edificio.h"
#include "ConfiguracionMapa.h"
#include <list>
#include <string>

class Mapa {
private:
	std::list<Figura*> elementos;
	std::list<Edificio*> edificiosPublicos;
	char contEdificiosPublicos;
	double areaEdificada;
	double areaArbolada;

	/* Crea un elemento del mapa. */
	void crearElemento(std::string tipo, std::list<Coordenada>& coordenadas,
			std::string radio, std::string nombrePublico);
	/* Exporta informacion de superficie. */
	void exportarSuperficies();
	/* Exporta el mapa. */
	void exportarMapa(const ConfiguracionMapa& configuracion);
	/* Si hay edificios publicos, exporta la referencia de cual es cada uno. */
	void exportarEdificiosPublicos();
public:
	Mapa();
	~Mapa();
	/* Lee el mapa y crea los objetos. */
	void leerObjetos(const char *archivo);
	/* Exporta el archivo entero. */
	void exportarArchivo(const ConfiguracionMapa& configuracion);
};

#endif /* MAPA_H_ */
