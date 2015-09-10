#ifndef SRC_SERVERPROXY_H_
#define SRC_SERVERPROXY_H_

#include "Socket.h"
#include <iostream>
#include <string>

class ServerProxy {
private:
	Socket *socket;
public:
	ServerProxy(std::string ip, std::string puerto);
	~ServerProxy();
	void informarSeccion(std::string nombreSeccion);
	void informarMediciones(unsigned int nivel, unsigned int cauce);
};

#endif /* SRC_SERVERPROXY_H_ */
