#ifndef K_MEANS_ONLINE
#define K_MEANS_ONLINE

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <time.h>
#include <list>
#include <fstream>
#include "omp.h"

//include modules
#include "maths_helpers.cpp"
#include "print_helper.cpp"
 
using namespace std;

void k_Means_Online(vector< vector<double> > data);

void k_Means_Online(vector< vector<double> > data){
	ofstream file;
	int k;
	double learnRate = 0.3;
	
	k = rand()%10 + 1;
	vector< vector<double> > centres(k, vector<double>(data[0].size(), 0));

	//Randomises the cluster centres
	for (int i = 0; i < centres.size(); i++)     
	{
		for (int j = 0; j < centres[0].size(); j++)
		{
			centres[i][j] = ((double) rand() / (RAND_MAX));
		}
	}

			cout << "Data: " << endl;
			Print_Data(data);
			cout << "k: " << k << endl;
			cout << "Centres: " << endl;
			Print_Data(centres);

	int it = 0;
	while(it < 50){

		for (int i = 0; i < data.size(); ++i){   //Finds nearest cluster centre and assigns a value in a vector corresponding to the closest centre
			int min_centre_index = 0;
			cout << "Distance from data[" << i << "] to centre[0] is " << Find_Distance(data[i], centres[min_centre_index]) << endl;
			for(int j = 1; j < centres.size(); ++j){
				cout << "Distance from data[" << i << "] to centre[" << j << "] is " << Find_Distance(data[i], centres[j]) << endl;
				if( Find_Distance(data[i], centres[j]) < Find_Distance(data[i], centres[min_centre_index]) ){
					min_centre_index = j;
				}
			}



			for(int k = 0;k < centres[min_centre_index].size();k++){
				centres[min_centre_index][k] = centres[min_centre_index][k] + learnRate * (data[i][k] - centres[min_centre_index][k]);
			}

		}

		/*learnRate = 1/(it + 1);  //Potential extra stopping condition*/


		it++;
	}


	Print_Data(centres);

	//Opens a file and prints the cluster centres in a csv format to plug into excel
	file.open("centres_online.csv", ios::app);
	for(int i = 0;i < centres.size();i++){
		file << centres[i][0];
    	for (int j = 1; j < centres[0].size(); j++)
    	{
    		file << "," << centres[i][j];
    	}
    	file <<  endl;
    }
    file.close();
}

#endif