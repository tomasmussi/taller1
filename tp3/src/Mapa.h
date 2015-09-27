#ifndef MAPA_H_
#define MAPA_H_

#include "Coordenada.h"
#include <list>
#include <string>

class Mapa {
private:
	void crearElemento(std::string tipo, std::list<Coordenada>& coordenadas,
			std::string radio);
public:
	Mapa();
	~Mapa();
	void leerObjetos(const char *archivo);
};

#endif /* MAPA_H_ */
