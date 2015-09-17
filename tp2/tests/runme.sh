#!/bin/bash

testcase=$1
echo "[[[test case: $testcase]]]"
port=$(./free_port.sh 3000)

rm -R runenv/*
if [ $? -ne 0 ] 
then
  echo "FAIL: rm failed"
  exit 1
fi
mkdir runenv/expected

cp ../bin/client ../bin/server runenv

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

for s in $(ls *.out __*)
do 
    diff $s expected/$s
    if [ $? -ne 0 ] 
    then
      echo "FAIL: $s"
      exit 1
    fi  
done

cd ..
sleep 1
