#ifndef MENSAJECONECTOR_H_
#define MENSAJECONECTOR_H_

#include <list>
#include <string>
#include <sstream>
#include "Medicion.h"

class MensajeConector {
private:
	std::string seccion;
	std::list<Medicion*> mediciones;
	std::list<Medicion*>::iterator iterador;
	void parsearSeccion(std::string mensaje);
public:
	MensajeConector(std::string mensaje);
	~MensajeConector();
	std::string getSeccion();
	bool hayActualizacion();
	Medicion* getMedicionActual();
	void avanzarMedicion();
};

#endif /* MENSAJECONECTOR_H_ */
