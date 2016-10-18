#!/bin/bash
	clusters=10;		#Number of clusters to be used
	
	./Make_Me_Data/Make_Me_Data 1000 2 > Test.txt
			
	./main.out s Test.txt $clusters e;
	./main.out p Test.txt $clusters e;
	
	
