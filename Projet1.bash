#!/usr/bin/bash
 
CSV=$1
NTHREAD=$2
PROG=$3


echo "nb_threads,temps" > $CSV

for ((n=1;n <= $NTHREAD;n++))
do 
	
	for ((i=1;i<=5;i++))
	do 
		echo -n "$n," >> $CSV
		/usr/bin/time -ao $CSV -f '%e' ./$PROG $n  >>/dev/null
	done 
done

