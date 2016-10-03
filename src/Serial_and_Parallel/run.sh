#!/bin/bash
	numTests=50;		#Number of increments to use
	numTestsRefinement=10;	#Number of refinements per increment
	increment=100;		#Increment amount

	for ((i=1; i<=$numTests; i++))
	do
		sumSerial=0;
		sumParallel=0;
		for ((j=0; j<$numTestsRefinement; j++))
		do
			#../Make_Me_Data/Make_Me_Data $(($i*$increment)) 2 > ../K-Means/Test.txt;
			sumSerial=$(echo $sumSerial + "$(./main.out $i*increment 3 1 0 s)" | bc -l);
			sumParallel=$(echo $sumParallel + "$(./main.out $i*increment 3 1 0 p)" | bc -l);
		done
		echo $(($i*$increment)),$(echo $sumSerial/$numTestsRefinement | bc -l),$(echo $sumParallel/$numTestsRefinement | bc -l)
	done
