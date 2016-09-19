#ifndef K_MEANS
#define K_MEANS

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <time.h>
#include <list>
#include <fstream>
#include "omp.h"
#include <sstream>

//include modules
#include "maths_helpers.cpp"
#include "print_helper.cpp"
 
using namespace std;

void k_Means(vector< vector<double> > data);
void parallel_k_Means(vector< vector<double> > data);

void k_Means(vector< vector<double> > data){
	ofstream file;
	int k;
	
	k = 10;//rand()%10 + 1;
	vector< vector<double> > centres(k, vector<double>(data[0].size(), 0));

	for (int i = 0; i < centres.size(); i++)     //Randomises the cluster centres
	{
		for (int j = 0; j < centres[0].size(); j++)
		{
			centres[i][j] = ((double) rand() / (RAND_MAX));
		}
	}

	vector<int> clusters_assignment(data.size());
			Print_Data("Data: ", data);
			Print_Data("k: ", k);
			Print_Data("Centres: ", centres);

	/*int it = 0;
	while(it < 1){

		for (int i = 0; i < data.size(); ++i){   //Finds nearest cluster centre and assigns a value in a vector corresponding to the closest centre
			int min_centre_index = 0;
			//cout << "Distance from data[" << i << "] to centre[0] is " << Find_Distance(data[i], centres[min_centre_index]) << endl;
			for(int j = 1; j < centres.size(); ++j){
				//cout << "Distance from data[" << i << "] to centre[" << j << "] is " << Find_Distance(data[i], centres[j]) << endl;
				if( Find_Distance(data[i], centres[j]) < Find_Distance(data[i], centres[min_centre_index]) ){
					min_centre_index = j;
				}
			}

			clusters_assignment[i] = min_centre_index;
		}



			cout << "Cluster-assignment: " << endl;
			Print_Data(clusters_assignment);
			cout << endl;
			cout << endl;




		for (int j = 0; j < k; j++) //Loops over clusters
		{
			int N = 0;
			vector<double> mean(centres[0].size(), 0);
			for(int i = 0;i < clusters_assignment.size();i++){ //Loops over the assignment of data to cluster
				if(clusters_assignment[i] == j){
					//cout << "data[" << i << "] is in cluster " << j << endl; 
					N++;
					for (int p = 0; p < mean.size(); p++) //Loops over the data and adds to a 'mean' vector
					{
						mean[p] += data[i][p];
					}

				}
			}
			for (int i = 0; i < mean.size(); ++i)
			{
				mean[i] /= N;
			}

			centres[j] = mean;



			//cout << "Mean of centre[" << j << "] is ";
			//Print_Data(mean);
		}
		it++;
	}*/


	/*Print_Data(centres);

	//Opens a file and prints the cluster centres in a csv format to plug into excel
	file.open("centres.csv", ios::app);
	for(int i = 0;i < centres.size();i++){
		file << centres[i][0];
    	for (int j = 1; j < centres[0].size(); j++)
    	{
    		file << "," << centres[i][j];
    	}
    	file <<  endl;
    }
    file.close();*/

}




void parallel_k_Means(vector< vector<double> > data){
	ofstream file;
	int k;
	
	k = 10;//rand()%10 + 1;
	vector< vector<double> > centres(k, vector<double>(data[0].size(), 0));

	int i;
	int j;
	#pragma omp parallel for collapse(2) private(j) num_threads(k)
	for (i = 0; i < centres.size(); i++)     //Randomises the cluster centres
	{
		for (j = 0; j < centres[0].size(); j++)
		{
			centres[i][j] = ((double) rand() / (RAND_MAX));
		}
	}

	vector<int> clusters_assignment(data.size());
			Print_Data("Data: ", data);
			Print_Data("k: ", k);
			Print_Data("Centres: ", centres);

	/*int it = 0;
	while(it < 1){

		int min_centre_index;
		//#pragma omp parallel for schedule(dynamic, 5) private(j, min_centre_index) num_threads(4) //collapse(2)
		#pragma omp parallel
		for (int i = 0; i < data.size(); ++i){   //Finds nearest cluster centre and assigns a value in a vector corresponding to the closest centre
			min_centre_index = 0;

			//cout << "Distance from data[" << i << "] to centre[0] is " << Find_Distance(data[i], centres[min_centre_index]) << endl;

			#pragma omp for nowait
			for(int j = 0; j < centres.size(); ++j){
				
				//cout << "Distance from data[" << i << "] to centre[" << j << "] is " << Find_Distance(data[i], centres[j]) << endl;

				if( Find_Distance(data[i], centres[j]) < Find_Distance(data[i], centres[min_centre_index]) ){
					min_centre_index = j;
					clusters_assignment[i] = min_centre_index;
				}
			}

			clusters_assignment[i] = min_centre_index;
		}



			cout << "Cluster-assignment: " << endl;
			Print_Data(clusters_assignment);
			cout << endl;
			cout << endl;



		#pragma omp parallel
		for (int j = 0; j < k; j++) //Loops over clusters
		{
			int N = 0;
			vector<double> mean(centres[0].size(), 0);

			#pragma omp for nowait private(mean)
			for(int i = 0;i < clusters_assignment.size();i++){ //Loops over the assignment of data to cluster
				if(clusters_assignment[i] == j){
					//cout << "data[" << i << "] is in cluster " << j << endl; 
					N++;
					for (int p = 0; p < mean.size(); p++) //Loops over the data and adds to a 'mean' vector
					{
						mean[p] += data[i][p];
					}

				}
			}
			for (int i = 0; i < mean.size(); ++i)
			{
				mean[i] /= N;
			}

			centres[j] = mean;



			//cout << "Mean of centre[" << j << "] is ";
			//Print_Data(mean);
		}
		it++;
	}*/


	/*Print_Data(centres);

	//Opens a file and prints the cluster centres in a csv format to plug into excel
	file.open("centres.csv", ios::app);
	for(int i = 0;i < centres.size();i++){
		file << centres[i][0];
    	for (int j = 1; j < centres[0].size(); j++)
    	{
    		file << "," << centres[i][j];
    	}
    	file <<  endl;
    }
    file.close();*/

}

#endif