/*
 *      Ejercicio [4] final 05/02/08
 * 		Asumiendo que la clase PARRAFO contiene un operador para 
 * 		escribirse en formato XML, escriba un operador« que vuelque 
 * 		a formato XML el contenido de std::array<PARRAFO>.
 */


#include "050208.4.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

ostream& operator<< (ostream& out, vector<Parrafo> vec) {
	out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
	for (size_t i=0; i<vec.size(); i++) {
		out << "<parrafo>" << endl;
		out << "  " << vec[i] << endl;
		out << "</parrafo>" << endl;
	}
	return out;
}

int main(int argc, char** argv) {
	
	Parrafo p1("este es el contenido del parrafo1");
	Parrafo p2("este es el contenido del parrafo2");
	Parrafo p3("este es el contenido del parrafo3");
	Parrafo p4("este es el contenido del parrafo4");
	
	vector<Parrafo> p_vec;
	p_vec.push_back(p1);
	p_vec.push_back(p2);
	p_vec.push_back(p3);
	p_vec.push_back(p4);
	
	ofstream xmlprueba("xmlprueba.xml");
	if (xmlprueba.is_open())
		xmlprueba << p_vec;
	else
		cout << p_vec;
		
	return 0;
}
