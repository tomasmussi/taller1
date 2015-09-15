#include "ClientProxy.h"

ClientProxy::ClientProxy(Socket *conexion, MapaConcurrenteHandler *mapa){
	this->conexion = conexion;
	this->mapa = mapa;
}

ClientProxy::~ClientProxy() {
}

void ClientProxy::run(){
	std::string mensaje = "";
	conexion->recibir(mensaje);
	while (! this->finMensaje(mensaje)){
		conexion->recibir(mensaje);
	}
	if (mensaje.find("conector seccion") != std::string::npos){
		this->resolverMensaje(mensaje);
	} else {
		std::string respuesta = mapa->imprimir();
		conexion->enviar(respuesta);
	}
	delete conexion;
}

bool ClientProxy::finMensaje(std::string mensaje){
	return mensaje.find("fin\n") != std::string::npos ||
			(mensaje.find("consultar") != std::string::npos && mensaje.find("\n"));
}

void ClientProxy::resolverMensaje(std::string mensajeString){
	/* Por el momento solo resuelvo los conectores */
	MensajeConector mensaje(mensajeString);
	std::string seccion = mensaje.getSeccion();
	while (mensaje.hayActualizacion()){
		Medicion *medicion = mensaje.getMedicionActual();
		mapa->actualizarMedicion(seccion, medicion);
		mensaje.avanzarMedicion();
	}
}
