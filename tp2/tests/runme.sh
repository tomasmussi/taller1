testcase=$1
port=$(./free_port.sh 3000)

rm -Rf runenv/*
mkdir runenv/expected

cp client server runenv

cp -f $testcase/in.zip runenv/
cp -f $testcase/out.zip runenv/expected
cp -f run.sh runenv/

cd runenv
unzip in.zip

cd expected
unzip out.zip
cd ..

./run.sh localhost $port "$2" single

for s in $(ls *.out __*)
do 
    diff $s expected/$s
    if [ $? -ne 0 ] 
    then
      echo "FAIL: $s"
      exit 1;
    fi  
done

cd ..
sleep 1
