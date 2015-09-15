#ifndef CLIENTPROXY_H_
#define CLIENTPROXY_H_

#include "server_MensajeConector.h"
#include "server_MapaConcurrenteHandler.h"
#include "common_Thread.h"
#include "common_Socket.h"

class ClientProxy : public Thread {
private:
	MapaConcurrenteHandler *mapa;
	Socket *conexion;
public:
	ClientProxy(Socket *conexion, MapaConcurrenteHandler *mapa);
	~ClientProxy();
	void run();
	bool finMensaje(std::string mensaje);
	std::string imprimir();
	void resolverMensaje(std::string mensajeString);
};

#endif /* CLIENTPROXY_H_ */
