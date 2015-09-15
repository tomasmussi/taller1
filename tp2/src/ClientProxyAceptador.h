#ifndef CLIENTPROXY_H_
#define CLIENTPROXY_H_

#include "Socket.h"
#include "Medicion.h"
#include "Thread.h"
#include <map>


class ClientProxyAceptador : public Thread{
private:
	bool seguir;
	Socket *socket;
	std::map<std::string, Medicion*> *secciones;
	bool finMensaje(std::string mensaje);
	void resolverMensaje(std::string mensajeString);

public:
	ClientProxyAceptador(std::string puerto);
	~ClientProxyAceptador();
	virtual void run();
	void escucharConexiones();
	void finalizar();
	void actualizarMedicion(std::string seccion, Medicion *medicion);
	std::string imprimir();
};

#endif /* CLIENTPROXY_H_ */
