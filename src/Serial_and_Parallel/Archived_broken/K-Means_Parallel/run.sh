#!/bin/bash
	varsum=0;
	for i in {1..50}
	do
		for j in {1..10}
		do
			../Make_Me_Data/Make_Me_Data $(($i*1000)) 2 > ../K-Means_Parallel/Test.txt;
			varsum=$(echo $varsum + "$(./P_K-means Test.txt)" | bc -l);
		done
		echo $(($i*1000)),$(echo $varsum/10.0 | bc -l)
	done
rm Test.txt
