#ifndef EDIFICIO_H_
#define EDIFICIO_H_

#include "Elemento.h"
#include "Poligono.h"
#include <list>
#include <string>

class Edificio: public Poligono {
private:
	char caracterInterno;
	std::string nombre;
public:
	explicit Edificio(const std::list<Coordenada>& coordenadas);
	Edificio(const std::list<Coordenada>& coordenadas,
			const std::string& nombre, const char caracter);
	bool superficieEdificada();
	bool superficieArbolada();
	const char caracter();
	const std::string getNombre();
	size_t nivel();
};

#endif /* EDIFICIO_H_ */
