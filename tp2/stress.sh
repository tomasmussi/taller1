END=1000;
for i in $(seq 1 $END); do 
	echo -ne "n 1 c 3\nn 0 c 2\nn 1 c 3\nn 2 c 3\nn 1 c 3\nn 2 c 3\n" | ./tp localhost socks S1 3; 
done
