#ifndef CLIENTPROXY_H_
#define CLIENTPROXY_H_

#include "Socket.h"

class ClientProxy {
private:
	Socket *socket;
public:
	ClientProxy(std::string puerto);
	~ClientProxy();
	void escucharConexiones();
};

#endif /* CLIENTPROXY_H_ */
