#!/bin/bash
	
	for i in {1..50}
	do
		sumSerial=0;
		sumParallel=0;
		for j in {1..10}
		do
			../Make_Me_Data/Make_Me_Data $(($i*1000)) 2 > ../K-Means/Test.txt;
			sumSerial=$(echo $sumSerial + "$(./SP_K-means Test.txt 15 s)" | bc -l);
			sumParallel=$(echo $sumParallel + "$(./SP_K-means Test.txt 15 p)" | bc -l);
		done
		echo $(($i*100)),$(echo $sumSerial/10.0 | bc -l),$(echo $sumParallel/10.0 | bc -l)
	done
