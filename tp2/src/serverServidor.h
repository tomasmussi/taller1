#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#include "serverClientProxyAceptador.h"
#include <string>

class Servidor {
private:
	ClientProxyAceptador proxy;
public:
	explicit Servidor(std::string puerto);
	~Servidor();
	void iniciar();
};

#endif /* SERVIDOR_H_ */
