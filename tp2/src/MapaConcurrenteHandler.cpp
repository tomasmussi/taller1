#include "MapaConcurrenteHandler.h"
#include "Lock.h"
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

std::string MapaConcurrenteHandler::imprimir(){
	Lock lock(mutex);
	std::ostringstream out;
	out << "Respuesta\n";
	for (std::map<std::string, Medicion*>::iterator it = this->secciones->begin(); it != this->secciones->end(); it++){
		out << "seccion " << it->first << " nivel " << it->second->getNivel() << " caudal " << it->second->getCaudal() << "\n";
	}
	out << "fin\n";
	return out.str();
}
