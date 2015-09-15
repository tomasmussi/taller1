#include "server_MapaConcurrenteHandler.h"
#include "common_Lock.h"
#include <sstream>

MapaConcurrenteHandler::MapaConcurrenteHandler() {
	this->secciones = new std::map<std::string, Medicion*>();
	this->mutex = new Mutex();
}

MapaConcurrenteHandler::~MapaConcurrenteHandler() {
	this->mutex->lock();
	for (std::map<std::string, Medicion*>::iterator it = this->secciones->begin(); it != this->secciones->end(); it++){
		delete it->second;
	}
	delete this->secciones;
	this->mutex->unlock();
	delete this->mutex;
}

void MapaConcurrenteHandler::actualizarMedicion(std::string seccion, Medicion *medicion){
	Lock lock(mutex);
	if (this->secciones->find(seccion) != this->secciones->end()){
		delete (*this->secciones)[seccion];
	}
	(*this->secciones)[seccion] = medicion;
}

std::string MapaConcurrenteHandler::imprimir(std::string seccion){
	Lock lock(mutex);
	std::ostringstream out;
	out << "respuesta\n";
	if (seccion != ""){
		if (this->secciones->find(seccion) != this->secciones->end()){
			Medicion *medicion = (*secciones)[seccion];
			out << "seccion " << seccion << " nivel " << medicion->getNivel() << " caudal " << medicion->getCaudal() << "\n";
		}
	} else {
		for (std::map<std::string, Medicion*>::iterator it = this->secciones->begin(); it != this->secciones->end(); it++){
			out << "seccion " << it->first << " nivel " << it->second->getNivel() << " caudal " << it->second->getCaudal() << "\n";
		}
	}
	out << "fin\n";
	return out.str();
}
