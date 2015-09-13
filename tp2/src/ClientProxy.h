#ifndef CLIENTPROXY_H_
#define CLIENTPROXY_H_

#include "Socket.h"
#include "Medicion.h"
#include <map>


class ClientProxy {
private:
	Socket *socket;
	std::map<std::string, Medicion*> *secciones;
	bool finMensaje(std::string mensaje);
	void resolverMensaje(std::string mensajeString);

public:
	ClientProxy(std::string puerto);
	~ClientProxy();
	void escucharConexiones();
	void actualizarMedicion(std::string seccion, Medicion *medicion);
	void imprimir();
};

#endif /* CLIENTPROXY_H_ */
