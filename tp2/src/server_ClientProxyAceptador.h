#ifndef CLIENTPROXYACEPTADOR_H_
#define CLIENTPROXYACEPTADOR_H_

#include "server_ClientProxy.h"
#include "server_MapaConcurrenteHandler.h"
#include "common_Socket.h"
#include "common_Medicion.h"
#include "common_Thread.h"
#include <list>

class ClientProxyAceptador : public Thread{
private:
	MapaConcurrenteHandler *mapa;
	Socket *socket;
	bool seguir;
	std::list<ClientProxy*> threads;
	bool clientesEliminados;
	bool finMensaje(std::string mensaje);
	void resolverMensaje(std::string mensajeString);
	void eliminarClientes();

public:
	ClientProxyAceptador(std::string puerto);
	~ClientProxyAceptador();
	virtual void run();
	void escucharConexiones();
	void finalizar();
};

#endif /* CLIENTPROXYACEPTADOR_H_ */
