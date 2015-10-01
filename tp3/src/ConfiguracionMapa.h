#ifndef CONFIGURACIONMAPA_H_
#define CONFIGURACIONMAPA_H_

#include "Calle.h"
#include "Celda.h"
#include <list>
#include <string>

class ConfiguracionMapa {
private:
	Calle calle;
	double latitudSuperior;
	double latitudInferior;
	double longitudIzquierda;
	double longitudDerecha;
	int alto;
	int ancho;
	std::list<Celda*> celdas;
	void parsearReal(std::string cadena, double& numero);
	void parsearEntero(std::string cadena, int& numero);
	void crearCeldas();
public:
	~ConfiguracionMapa();
	/* Parsea los datos de borde del mapa y las divisiones. */
	bool leerArchivo(const char *archivo);
	/* Devuelve las celdas creadas para que el mapa las utilice. */
	const std::list<Celda*> getCeldas() const;
	/* Devuelve el ancho del mapa. */
	int getAncho() const;
};

#endif /* CONFIGURACIONMAPA_H_ */
