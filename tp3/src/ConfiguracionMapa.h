#ifndef CONFIGURACIONMAPA_H_
#define CONFIGURACIONMAPA_H_

#include <string>

class ConfiguracionMapa {
private:
	double latitudSuperior;
	double latitudInferior;
	double longitudIzquierda;
	double longitudDerecha;
	int alto;
	int ancho;
	void parsearReal(std::string cadena, double& numero);
	void parsearEntero(std::string cadena, int& numero);
public:
	ConfiguracionMapa();
	~ConfiguracionMapa();
	bool leerArchivo(const char *archivo);
};

#endif /* CONFIGURACIONMAPA_H_ */
