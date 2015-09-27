#ifndef COORDENADA_H_
#define COORDENADA_H_

#include <ostream>

class Coordenada {
private:
	double latitud;
	double longitud;
	void parsearReal(std::string cadena, double& numero);
public:
	Coordenada();
	Coordenada(std::string& latitud, std::string& longitud);
	~Coordenada();
	double getLatitud();
	double getLongitud();
	friend std::ostream& operator<<(std::ostream& os, const Coordenada& obj);
};

#endif /* COORDENADA_H_ */
