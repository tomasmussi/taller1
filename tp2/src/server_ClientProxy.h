#ifndef CLIENTPROXY_H_
#define CLIENTPROXY_H_

#include "server_MapaConcurrenteHandler.h"
#include "common_Thread.h"
#include "common_Socket.h"

class ClientProxy : public Thread {
private:
	MapaConcurrenteHandler *mapa;
	Socket *conexion;
	bool finalizado;
	std::string buffer;
	std::string seccion;
	bool interpretarEnviado(std::string enviado);
	bool ejecutarComando(std::string comando);
public:
	ClientProxy(Socket *conexion, MapaConcurrenteHandler *mapa);
	~ClientProxy();
	void run();
	bool finMensaje(std::string mensaje);
	std::string imprimir();
	bool finalizar();
};

#endif /* CLIENTPROXY_H_ */
