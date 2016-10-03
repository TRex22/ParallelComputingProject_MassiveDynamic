#!/bin/bash
#This runs the timed serial k-means algorithm and outputs the x,y pair where x is the number of data points and y is the average time taken for n iterations. Variables can be changed below:
	numberOfRuns=50;
	multiple=100;
	iterationsPerMultiple=100;
	dimension=3;
	
	sum=0;
	for ((i=1; i<=$numberOfRuns; i++))
	do
		for ((j=0; j<$iterationsPerMultiple; j++))
		do
			../Make_Me_Data/Make_Me_Data $(($i*$iterationsPerMultiple)) $dimension > ../K-Means_Serial/Test.txt;
			sum=$(echo $sum + "$(./S_K-means Test.txt)" | bc -l);
		done
		echo $(($i*$multiple)),$(echo $sum/$iterationsPerMultiple | bc -l)
	done
