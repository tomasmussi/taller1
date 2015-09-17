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
	std::list<ClientProxy*> threads;
	bool seguir;
	Socket *socket;
	MapaConcurrenteHandler *mapa;
	bool finMensaje(std::string mensaje);
	void resolverMensaje(std::string mensajeString);

public:
	ClientProxyAceptador(std::string puerto);
	~ClientProxyAceptador();
	virtual void run();
	void escucharConexiones();
	void finalizar();
};

#endif /* CLIENTPROXYACEPTADOR_H_ */
