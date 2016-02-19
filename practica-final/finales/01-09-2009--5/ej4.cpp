#include <pthread.h>

class Thread {
// esta es la implementacion basica de un thread. Todo hilo tendra que heredar de este.
protected:
	// este es el metodo que habra que sobreescribir. Es el metodo que hara el trabajo
	// que querramos que haga el thread.
	virtual void correr() = 0;
private:
	// esta funcion de callback es importante, es la que llama pthread_create
	static void* callback(void* aux) {
		((Thread*) aux)->correr();
		return 0;
	}
	// struct que tiene la informacion de pthread
	pthread_t thread;
	bool cr; 	
public:
	Thread(): cr(false){}
	
	virtual ~Thread() {}
	
	// al iniciar el hilo, se ahce pthread_create
	// los parametros son:
	// 1) la estructura pthread_t
	// 2) atributos que se le quiera asignar al thread en momento de creacion (NULL si no se quiere nada)
	// 3) puntero a la funcion de callbak que va a llamar
	// 4) argumento que recibira la funcion de callback
	void iniciar() {
		cr = true;
		pthread_create(&thread, 0, Thread::callback, this);
	}
	
	void detener() {
		cr = false;
	}
	
	// Este metodo sincroniza los hilos
	// la funcion POSIX llamada es pthread_join, que recibe:
	// 1) la estructura pthread_t que este ejecutandose
	// 2) Un puntero a donde queremos que guarde el valor de retorno de la funcion de callback,
	// si no queremos que nos retorne nada, pasamos NULL
	void sincronizar() {
		pthread_join(thread, NULL); 
	}
	
	bool corriendo() {
		return cr;
	}
};

class Producer : public Thread {
// como atributo privado tendria algo del estilo:
// ColaBloqueante& cola;
// que seria una referencia a una cola compartida entre el Producer y el Consumer
public:
	void correr() {
		while (corriendo()) {
			// aca haria cosas que luego encolaria
			// por ejemplo, espero cosas de un socket
			// o de un archivo
		}
	}
};

class Consumer : public Thread {
// como atributo privado tendria algo del estilo:
// ColaBloqueante& cola;
// que seria una referencia a una cola compartida entre el Producer y el Consumer
public:
	void correr() {
		while (corriendo()) {
			// aca estaria esperando a que haya elementos en una
			// cola
			// si los hay, ejecuto lo que tenga que ejecutar
			// por ejemplo, mostrar los datos por pantalla
		}
	}
};

int main(int argc, char** argv) {
	// ahora vemos el uso apropiado
	Producer producer;
	Consumer consumer;

	// Asi inicio los hilos. Esto hace que se haga el llamado a iniciar de
	// Thread, llamando a la funcion de callback. Notar que el correr() es
	// polimorfico
	producer.iniciar();
	consumer.iniciar();

	// Esta linea detiene los hilos PERO NO LOS SINCRONIZA. Lo unico que
	// hace es detener la ejecucion de su hilo principal, pero siguen
	// abiertos los recursos.
	producer.detener();
	consumer.detener();

	// En estas lineas se sincronizan los hilos al hilo principal. Es el
	// analogo a cerrar un archivo. Es de tener en cuenta que si los hilos
	// no se detuvieron, el sincronizar va a esperar a que terminen con su
	// tarea y luego sincronizara. Es bloqueante.
	producer.sincronizar();
	consumer.sincronizar();
	return 0;
}
