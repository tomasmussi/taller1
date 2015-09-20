#include "server_MapaConcurrenteHandler.h"
#include "common_Lock.h"

#include <sstream>

MapaConcurrenteHandler::MapaConcurrenteHandler() {
}

MapaConcurrenteHandler::~MapaConcurrenteHandler() {
	mutex.lock();
	for (std::map<std::string, Medicion*>::iterator it = secciones.begin();
			it != secciones.end(); it++){
		delete it->second;
	}
	mutex.unlock();
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
