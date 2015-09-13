#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#include "ClientProxy.h"

class Servidor {
private:
	ClientProxy *proxy;
public:
	Servidor(std::string puerto);
	~Servidor();
	void iniciar();
};

#endif /* SERVIDOR_H_ */
