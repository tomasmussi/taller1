#!/bin/bash
set -x

if [ "$1" == "--help" ] || [ $# -lt 2 ]; then
	echo -e "Uso: run.sh puerto args_server [valgrind]\n"
	exit -1
fi

server_host=$1
puerto=$2
modo=$4
cant_lientes=5
server="server"
client="client"

if [ "$3" == "valgrind" ]; then
	pre_server='valgrind --gen-suppressions=all --tool=memcheck --trace-children=yes --track-fds=yes --time-stamp=yes --num-callers=20 --error-exitcode=42 --db-attach=no --leak-check=full --leak-resolution=med --log-file=valgrind_server.out '
	pre_client='valgrind --gen-suppressions=all --tool=memcheck --trace-children=yes --track-fds=yes --time-stamp=yes --num-callers=20 --error-exitcode=42 --db-attach=no --leak-check=full --leak-resolution=med --log-file=valgrind_client$n.out '
fi

echo "Probando caso en puerto $1 $2 en modo $4 $3"

shift
shift
shift
shift

echo -n "Server..."
mkfifo server-stdin
$pre_server ./$server $puerto "$@" <> server-stdin > __server_stdout__ 2> __server_stderr__ &
sleep 1
ps $! > /dev/null
server_status=$? 
if [ $! -gt 0 ] && [ $server_status -eq 0 ]; then
	echo -e "OK\nServer PID $!"
	server_pid=$!
else
	echo "Error"
	rm server-stdin
	exit 2
fi


for (( n=0; n < $cant_lientes; n++ )); do
	if [ -f "netcat$n.in" ]; then	
		if [ "$modo" == "single" ]; then
			echo "Netcat $n"
			eval nc $server_host $puerto < netcat$n.in > netcat$n.out
		else
			mkfifo input_netcat$n
			eval nc $server_host $puerto <> input_netcat$n > netcat$n.out &
		fi
	fi
	if [ -f "client$n.in" ]; then
		if [ -f "client$n.args" ]; then
			client_args=$(cat client$n.args)
		fi
		if [ "$modo" == "single" ]; then
			echo "Cliente $n"
			eval $pre_client ./$client $server_host $puerto $client_args < client$n.in > client$n.out
		else
			mkfifo input_cliente$n
			eval $pre_client ./$client $server_host $puerto $client_args <> input_cliente$n > client$n.out &
		fi
	fi
done

if [ "$modo" == "multiple" ]; then
	for (( n=0; n < $cant_lientes; n++ )); do
		if [ -f "netcat$n.in" ]; then
			echo "Netcat $n"
			eval cat netcat$n.in > input_netcat$n
		fi
		if [ -f "client$n.in" ]; then
			echo "Cliente $n"
			eval cat client$n.in > input_cliente$n
		fi
	done
	sleep 3
	for (( n=0; n < $cant_lientes; n++ )); do
	  	if [ -f "netcat$n.in" ]; then
			echo "Borrando Pipe Netcat $n"
			rm input_netcat$n
		fi
	  	if [ -f "client$n.in" ]; then
			echo "Borrando Pipe Cliente $n"
			rm input_cliente$n
		fi
	done
fi

echo -n "Terminando server..."
echo -e "q\n" >> server-stdin
sleep 1
rm -f server-stdin
if [ "$?" = "0" ]; then
	echo "Server detenido OK"
else
	echo "Server ERROR"
	kill -9 $server_pid
fi
