#ifndef _PARRAFO_H__
#define _PARRAFO_H__

#include <string>
#include <iostream>

class Parrafo {

private:
	std::string _texto;
	
public:
	Parrafo(const std::string& texto){
		_texto=texto;
	}
	~Parrafo(){}
	std::string getTexto() const {
		return _texto;
	}
};

/* implementacion de << */
std::ostream& operator<< (std::ostream& out, const Parrafo& p) {
	out << p.getTexto();
	return out;
}

#endif
