#ifndef EDIFICIO_H_
#define EDIFICIO_H_

#include "Elemento.h"
#include "Poligono.h"

class Edificio: public Poligono {
private:
	char caracterInterno;
	std::string nombre;
public:
	explicit Edificio(std::list<Coordenada> coordenadas);
	Edificio(std::list<Coordenada> coordenadas, std::string nombre,
			char caracter);
	~Edificio();
	bool superficieEdificada();
	bool superficieArbolada();
	const char caracter();
	const std::string getNombre();
	size_t nivel();
};

#endif /* EDIFICIO_H_ */
