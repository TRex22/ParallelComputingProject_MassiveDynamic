#!/bin/bash
	varsum=0;
	for i in {1..3}
	do
		for j in {1..100}
		do
			../Make_Me_Data/Make_Me_Data $(($i*100)) 3 > ../K-Means_Serial/Test.txt;
			varsum=$(echo $varsum + "$(./S_K-means Test.txt)" | bc -l);
		done
		echo $(($i*100)),$(echo $varsum/100.0 | bc -l)
	done
	rm Test.txt
