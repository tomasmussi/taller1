#ifndef SRC_SERVERPROXY_H_
#define SRC_SERVERPROXY_H_

class ServerProxy {
public:
	ServerProxy();
	~ServerProxy();
	void informarMediciones(unsigned int nivel, unsigned int cauce);
};

#endif /* SRC_SERVERPROXY_H_ */
