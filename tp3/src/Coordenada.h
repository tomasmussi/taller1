#ifndef COORDENADA_H_
#define COORDENADA_H_

#include <string>
#include <ostream>

class Coordenada {
private:
	double _latitud;
	double _longitud;
	void parsearReal(const std::string& cadena, double& numero);
public:
	Coordenada(const std::string& latitud, const std::string& longitud);
	Coordenada(double longitud, double latitud);
	double latitud() const;
	double longitud() const;
};

#endif /* COORDENADA_H_ */
