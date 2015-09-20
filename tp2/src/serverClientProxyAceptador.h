#ifndef CLIENTPROXYACEPTADOR_H_
#define CLIENTPROXYACEPTADOR_H_

#include "serverClientProxy.h"
#include "serverMapaConcurrenteHandler.h"
#include "commonSocket.h"
#include "commonMedicion.h"
#include "commonThread.h"
#include <string>
#include <list>

class ClientProxyAceptador : public Thread{
private:
	MapaConcurrenteHandler mapa;
	Socket socket;
	bool seguir;
	std::list<ClientProxy*> threads;
	bool clientesEliminados;
	bool finMensaje(std::string mensaje);
	void resolverMensaje(std::string mensajeString);
	void eliminarClientes();

public:
	explicit ClientProxyAceptador(std::string puerto);
	~ClientProxyAceptador();
	virtual void run();
	void escucharConexiones();
	void finalizar();
};

#endif /* CLIENTPROXYACEPTADOR_H_ */
