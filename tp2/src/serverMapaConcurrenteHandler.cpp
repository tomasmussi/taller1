#include "serverMapaConcurrenteHandler.h"
#include "commonLock.h"

#include <string>
#include <sstream>
#include <map>

/* Monitor del recurso compartido map para consultas y actualizaciones. */
MapaConcurrenteHandler::MapaConcurrenteHandler() {
}

MapaConcurrenteHandler::~MapaConcurrenteHandler() {
	Lock lock(&mutex);
	for (std::map<std::string, Medicion*>::iterator it = secciones.begin();
			it != secciones.end(); it++){
		delete it->second;
	}
}

void MapaConcurrenteHandler::actualizarMedicion(std::string seccion,
		Medicion *medicion){
	Lock lock(&mutex);
	if (secciones.find(seccion) != secciones.end()){
		delete secciones[seccion];
	}
	secciones[seccion] = medicion;
}

void MapaConcurrenteHandler::armarMensaje(std::ostringstream& out,
		Medicion *medicion, std::string seccion){
	out << "seccion " << seccion << " nivel " << medicion->getNivel()
			<< " caudal " << medicion->getCaudal() << "\n";
}

std::string MapaConcurrenteHandler::imprimir(std::string seccion){
	Lock lock(&mutex);
	std::ostringstream out;
	out << "respuesta\n";
	if (seccion != ""){
		if (secciones.find(seccion) != secciones.end()){
			this->armarMensaje(out, secciones[seccion], seccion);
		}
	} else {
		for (std::map<std::string, Medicion*>::iterator it = secciones.begin();
				it != secciones.end(); it++){
			this->armarMensaje(out, it->second, it->first);
		}
	}
	out << "fin\n";
	return out.str();
}
