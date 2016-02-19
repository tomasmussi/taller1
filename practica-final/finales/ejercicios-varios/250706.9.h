/*
 *      Ejercicio [9] coloquio 25/07/06
 * 		Declarar una clase Arreglo<T> que permita organizar una
 * 		coleccion de objetos T en un arreglo. Incluya constructor
 *		default, de copia, operador <<, =, [] e int.
 */
 
 #ifndef _ARREGLO_H__
 #define _ARREGLO_H__
 
 #include <iostream>
  
 // declaracion
 // ===========
 
 template <typename T>
 class Arreglo {
 
 private:
 	T* _elems;
 	int _tope;
 	int _nElem;
 
 public:
 	Arreglo( int N=20 );
 	Arreglo( const Arreglo& arreglo);
 	~Arreglo( );
 	void agregar(T elem);
 	template <typename G> friend std::ostream& 
 		operator<< (std::ostream& out,
 		const Arreglo<G>& arreglo);
 	Arreglo& operator+(const Arreglo& arr2);
 	Arreglo& operator=( const Arreglo& arreglo );
 	T& operator[](unsigned int i);
};

// implementacion
// ==============
 
 	// constructor default y con parametro con valor default
 	// si no se especifica parametro de entrada se construye un 
 	// arreglo de 20 elementos
 	template <typename T> Arreglo<T>::Arreglo( int N ) {
 		_elems = new T[N];
 		_nElem=0;
 		_tope=N;
 	};
 	
 	// constructor de copia
 	template <typename T> Arreglo<T>::Arreglo( const Arreglo<T>& arreglo){
 		_elems = new T[arreglo._tope];
 		for (int i=0; i<arreglo._nElem; i++)
 			_elems[i]=arreglo._elems[i];
 		_nElem = arreglo._nElem;
 	};
 	
 	// destructor
 	template <typename T> Arreglo<T>::~Arreglo( ) {
 		delete [] _elems;
 	};
 	
 	// agrega elementos al arreglo
 	template <typename T> void Arreglo<T>:: agregar(T elem) {
 		if (_nElem<_tope){
 			_elems[_nElem]=elem;
 			_nElem++;
 		}
 	};
 	
 	// operador <<
 	template <typename T> std::ostream& operator<< (std::ostream& out,
 		const Arreglo<T>& arreglo) {
 		for (int i=0; i<arreglo._nElem; i++)
 			out << arreglo._elems[i] << std::endl;
 		return out;
 	};
 	
 	// operador +
 	template <typename T> Arreglo<T>& Arreglo<T>:: operator+(const Arreglo<T>& arr2) {
 		// asumo ambos tienen la misma cantidad de elementos
 		for (int i = 0; i<_nElem; i++){
 			_elems[i]+=arr2._elems[i];
 		}
 		return *this;
 	};
 	
 	// operador =
 	template <typename T> Arreglo<T>& Arreglo<T>:: operator=( const Arreglo<T>& arreglo ) {
 		// asumo que ambos arreglos tienen la misma 
 		// cantidad de elementos
 			for (int i=0; i<arreglo._nElem; i++){
 				_elems[i]=arreglo._elems[i];
 				_nElem++;
 			}
 		return *this;
 	};
 	
 	// operador []
 	template <typename T> T& Arreglo<T>:: operator[](unsigned int i) {
 		if (_nElem<i)
 			return _elems[_nElem];
 		return _elems[i];
 	};
 
 
 #endif
