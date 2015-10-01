#ifndef COORDENADA_H_
#define COORDENADA_H_

#include <string>
#include <ostream>

class Coordenada {
private:

	void parsearReal(std::string cadena, double& numero);
public:
	double latitud;
	double longitud;
	Coordenada();
	Coordenada(std::string& latitud, std::string& longitud);
	Coordenada(double longitud, double latitud);
	~Coordenada();
	double getLatitud() const;
	double getLongitud() const;
	double distanciaCon(const Coordenada& otroPunto) const;
	bool operator==(const Coordenada &otro) const;
	friend std::ostream& operator<<(std::ostream& os, const Coordenada& obj);
};

#endif /* COORDENADA_H_ */
