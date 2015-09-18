#!/bin/bash

testcase=$1
echo "[[[test case: $testcase]]]"
port=$(./free_port.sh 3000)

rm -Rf runenv/*
$(rm -Rf backup/$testcase)

if [ $? -ne 0 ] 
then
  echo "FAIL: rm failed"
  exit 1
fi
mkdir runenv/expected
$(mkdir backup/$testcase)

cp ../bin/client runenv/client
cp ../bin/server runenv/server

cp -f $testcase/in.zip runenv/
cp -f $testcase/out.zip runenv/expected
cp -f run.sh runenv/

cd runenv
unzip in.zip

cd expected
unzip out.zip
cd ..

./run.sh localhost $port "$2" single
if [ $? -ne 0 ] 
then
  echo "FAIL: run.sh failed"
  exit 1
fi

if [ $2 == "valgrind" ]
then
	for f in $(ls valgrind*)
	do
		$(mv $f ../backup/$testcase/$f)
	done
fi

for s in $(ls *.out __*)
do 
    diff $s expected/$s
    if [ $? -ne 0 ] 
    then
      echo "FAIL: $s"
      exit 1
    fi  
done

for f in $(ls ../backup/$testcase)
do
	cat ../backup/$testcase/$f | grep -q "All heap blocks were freed -- no leaks are possible"
	if [ $? -ne 0 ]
	then
		echo "VALGRIND FAIL: $f"
		exit 1
	fi
done

cd ..
sleep 1
