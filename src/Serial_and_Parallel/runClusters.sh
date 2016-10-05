#!/bin/bash
	numTests=50;		#Number of increments to use
	refinements=10;		#Number of refinements per increment
	increment=1;		#Increment amount
	dimension=2;		#Dimension of data (and implicitly, clusters)
	datapoints=200;		#Number of datapoints to be used
	
	#Print critical data to aid analysis
	echo Datapoints used:,$datapoints;
	echo Dimension:,$dimension;
	
	#Headings per column
	echo numClusters,serialTime,parallelTime

	for ((i=1; i<=$numTests; i++))
	do
		sumSerial=0;
		sumParallel=0;
		for ((j=0; j<$refinements; j++))
		do
			./Make_Me_Data/Make_Me_Data $datapoints $dimension > Test.txt
			
			sumSerial=$(echo $sumSerial + "$(./main.out s Test.txt $i*$increment)" | bc -l);
			sumParallel=$(echo $sumParallel + "$(./main.out p Test.txt $i*$increment)" | bc -l);
		done
		echo $(($i*$increment)),$(echo $sumSerial/$refinements | bc -l),$(echo $sumParallel/$refinements | bc -l)
	done
