#ifndef MAPACONCURRENTEHANDLER_H_
#define MAPACONCURRENTEHANDLER_H_

#include "commonMedicion.h"
#include "commonMutex.h"
#include <map>

class MapaConcurrenteHandler {
private:
	std::map<std::string, Medicion*> secciones;
	Mutex mutex;
	void armarMensaje(std::ostringstream& out, Medicion *medicion,
			std::string seccion);
public:
	MapaConcurrenteHandler();
	~MapaConcurrenteHandler();
	void actualizarMedicion(std::string seccion, Medicion *medicion);
	std::string imprimir(std::string seccion);
};

#endif /* MAPACONCURRENTEHANDLER_H_ */
