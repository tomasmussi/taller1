#include <stdlib.h>

#define TAM 20


template < class T >
class Vector {
	public:
		Vector();
		~Vector();
		void add(const T &elemento);
		T operator[](int indice);
	private:
		T *vector_;
		int indice_;
		int tamanio_;
};

template < class T >
Vector<T>::Vector() {
	vector_ = (T*) malloc(TAM * sizeof(T));
	indice_ = 0;
	tamanio_ = TAM;
}

template < class T >
Vector<T>::~Vector() {
	free(vector_);
}


template < class T >
void Vector<T>::add(const T &elemento) {
	if (indice_ == tamanio_) {
		// Redimensionar
	}
	vector_[indice_++] = elemento;
}

template < class T >
T Vector<T>::operator[](int indice) {
	return vector_[indice];
}
