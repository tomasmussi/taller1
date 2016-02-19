#include <sys/socket.h>
#include <sys/type.h>

int main(int argc, char** argc) {
	// esto crea un socket con protocolo TCP (SOCK_STREAM) IP (AF_INET)
	int fdsock = socket(AF_INET, SOCK_STREAM, 0);
	
	// la struct sockaddr_in es para poder hacer el bind del socket
	struct sockaddr_in direccion;
	// esto rellena el padding
	memset((char*)&direccion, 0, sizeof(direccion));
	// aclara que es IP
	direccion.sin_family = AF_INET;
	// el puerto elegido, en este caso 1172
	// notar que se usa htons que transforma al formato adecuado para sin_port
	direccion.sin_port = htons(1172);
	// host, en nuestro caso, INADDR_ANY para poder escuchar conexiones entrantes
	direccion.sin_addr.s_addr = INADDR_ANY;
	
	// ahora hacemos bind. NOTA: no realizaremos validaciones
	bind(fdsock, (struct sockaddr*)&direccion, (socklen_t) sizeof(struct sockaddr));

	// una vez nombrado, procedemos a escuchar. El numero que acompaña al filedescriptor
	// es la cantidad de conexiones en simultaneo que puede tener el servidor en la cola de espera
	// elegimos arbitrariamente 5
	// NOTA: listen marca al socket como para ESCUCHAR, no devuelve un fd
	listen(fdsock, 5);
	// accept nos devuelve el fd de escuchar
	int conexion = accept(fd, (struct sockaddr*)&direccion, sizeof(struct sockaddr));
	// de aca en adelante vendria el codigo para poder recibir paquetes. Es un simple ciclo while, donde
	// se reciba info con recv(fdsock, &buffer, sizeof(char), 0);
} 
