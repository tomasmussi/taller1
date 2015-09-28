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
	ConfiguracionMapa();
	~ConfiguracionMapa();
	bool leerArchivo(const char *archivo);
	const std::list<Celda*> getCeldas() const;
	int getAncho() const;
};

#endif /* CONFIGURACIONMAPA_H_ */
