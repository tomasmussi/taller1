#ifndef MAPACONCURRENTEHANDLER_H_
#define MAPACONCURRENTEHANDLER_H_

#include "common_Medicion.h"
#include "common_Mutex.h"
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
