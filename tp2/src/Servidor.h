#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#include "ClientProxyAceptador.h"

class Servidor {
private:
	ClientProxyAceptador *proxy;
public:
	Servidor(std::string puerto);
	~Servidor();
	void iniciar();
};

#endif /* SERVIDOR_H_ */
