#ifndef MAPACONCURRENTEHANDLER_H_
#define MAPACONCURRENTEHANDLER_H_

#include "Medicion.h"
#include "Mutex.h"
#include <map>

class MapaConcurrenteHandler {
private:
	std::map<std::string, Medicion*> *secciones;
	Mutex *mutex;
public:
	MapaConcurrenteHandler();
	~MapaConcurrenteHandler();
	void actualizarMedicion(std::string seccion, Medicion *medicion);
	std::string imprimir(std::string seccion);
};

#endif /* MAPACONCURRENTEHANDLER_H_ */
