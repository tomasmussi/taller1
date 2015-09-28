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

	void crearElemento(std::string tipo, std::list<Coordenada>& coordenadas,
			std::string radio, std::string nombrePublico);
	void exportarSuperficies();
	void exportarMapa(const ConfiguracionMapa& configuracion);
	void exportarEdificiosPublicos();
public:
	Mapa();
	~Mapa();
	void leerObjetos(const char *archivo);
	void exportarArchivo(const ConfiguracionMapa& configuracion);
};

#endif /* MAPA_H_ */
