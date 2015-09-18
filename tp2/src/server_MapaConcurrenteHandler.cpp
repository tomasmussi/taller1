#include "server_MapaConcurrenteHandler.h"
#include "common_Lock.h"

#include <sstream>

MapaConcurrenteHandler::MapaConcurrenteHandler() : secciones(), mutex() {
}

MapaConcurrenteHandler::~MapaConcurrenteHandler() {
	mutex.lock();
	for (std::map<std::string, Medicion*>::iterator it = secciones.begin(); it != secciones.end(); it++){
		delete it->second;
	}
	mutex.unlock();
}

void MapaConcurrenteHandler::actualizarMedicion(std::string seccion, Medicion *medicion){
	Lock lock(&mutex);
	if (secciones.find(seccion) != secciones.end()){
		delete secciones[seccion];
	}
	secciones[seccion] = medicion;
}

std::string MapaConcurrenteHandler::imprimir(std::string seccion){
	Lock lock(&mutex);
	std::ostringstream out;
	out << "respuesta\n";
	if (seccion != ""){
		if (secciones.find(seccion) != secciones.end()){
			Medicion *medicion = secciones[seccion];
			out << "seccion " << seccion << " nivel " << medicion->getNivel() << " caudal " << medicion->getCaudal() << "\n";
		}
	} else {
		for (std::map<std::string, Medicion*>::iterator it = secciones.begin(); it != secciones.end(); it++){
			out << "seccion " << it->first << " nivel " << it->second->getNivel() << " caudal " << it->second->getCaudal() << "\n";
		}
	}
	out << "fin\n";
	return out.str();
}
