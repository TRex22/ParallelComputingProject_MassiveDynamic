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
#include "output_helper.cpp"
#include "print_helper.cpp"
 
using namespace std;

vector<string> k_Means(vector< vector<double> > data, const bool webmode);
vector<string> parallel_k_Means(vector< vector<double> > data, const bool webmode);

vector<string> k_Means(vector< vector<double> > data, const bool webmode){
	vector<string> output = {"", ""};
	int k;
	
	k = 10;//rand()%10 + 1;
	vector<vector<double>> centres(k, vector<double>(data[0].size(), 0));

	for (int i = 0; i < centres.size(); i++)     //Randomises the cluster centres
	{
		for (int j = 0; j < centres[0].size(); j++)
		{
			centres[i][j] = ((double) rand() / (RAND_MAX));
		}
	}

	vector<int> clusters_assignment(data.size());

	output = Get_Data(output, "data", data);
	output = Get_Data(output, "k", k);
	output = Get_Data(output, "centres_start", centres);

	int it = 0;
	while(it < 200)
	{

		for (int i = 0; i < data.size(); ++i)   //Finds nearest cluster centre and assigns a value in a vector corresponding to the closest centre
		{   
			int min_centre_index = 0;
			
			for(int j = 1; j < centres.size(); ++j)
			{
				if( Find_Distance(data[i], centres[j]) < Find_Distance(data[i], centres[min_centre_index]) )
				{
					min_centre_index = j;
				}
			}

			clusters_assignment[i] = min_centre_index;
		}

		for (int j = 0; j < k; j++) //Loops over clusters
		{
			int N = 0;   //counter for how many points in a cluster
			vector<double> mean(centres[0].size(), 0);
			for(int i = 0;i < clusters_assignment.size();i++)  //Loops over the assignment of data to cluster
			{ 
				if(clusters_assignment[i] == j)
				{
					N++;
					for (int p = 0; p < mean.size(); p++)  //Loops over the data and adds to a 'mean' vector
					{
						mean[p] += data[i][p];
					}

				}
			}

			for (int i = 0; i < mean.size(); ++i)
			{
				if(mean[i] != 0){
					mean[i] /= N;
				}
			}

			centres[j] = mean;
		}
		it++;
	}

	double Mean_Sq_Err = Mean_Squared_Error(data, centres);

	output = Get_Data(output, "centres", centres);
	output = Get_Data(output, "error", Mean_Sq_Err);

	return output;
}




vector<string> parallel_k_Means(vector< vector<double> > data, const bool webmode){
	ofstream file;
	vector<string> output = {"", ""};
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
	
	output = Get_Data(output, "data", data);
	output = Get_Data(output, "k", k);
	output = Get_Data(output, "centres_start", centres);

	int it = 0;
	while(it < 200)
	{
		int min_centre_index;
		//#pragma omp parallel for schedule(dynamic, 5) private(j, min_centre_index) num_threads(4) //collapse(2)
		#pragma omp parallel
		for (int i = 0; i < data.size(); ++i)   //Finds nearest cluster centre and assigns a value in a vector corresponding to the closest centre
		{   
			min_centre_index = 0;

			#pragma omp for nowait
			for(int j = 0; j < centres.size(); ++j)
			{				
				if(Find_Distance(data[i], centres[j]) < Find_Distance(data[i], centres[min_centre_index]))
				{
					min_centre_index = j;
					clusters_assignment[i] = min_centre_index;
				}
			}

			clusters_assignment[i] = min_centre_index;
		}

		Print_Data("clusters assignment", clusters_assignment);

		#pragma omp parallel for
		for (int j = 0; j < k; j++) //Loops over clusters
		{
			int N = 0;
			vector<double> mean(centres[0].size(), 0);

			for(int i = 0;i < clusters_assignment.size();i++)
			{ //Loops over the assignment of data to cluster
				if(clusters_assignment[i] == j){
					N++;
					for (int p = 0; p < mean.size(); p++) //Loops over the data and adds to a 'mean' vector
					{
						mean[p] += data[i][p];
					}
				}
			}
			for (int i = 0; i < mean.size(); ++i)
			{
				if(mean[i] != 0){
					mean[i] /= N;
				}
			}

			centres[j] = mean;
		}
		it++;
	}

	double Mean_Sq_Err = Mean_Squared_Error(data, centres);

	output = Get_Data(output, "centres", centres);
	output = Get_Data(output, "error", Mean_Sq_Err);

	/*Print_File("data-par.csv", data);
	Print_File("centres-par.csv", centres);*/

	return output;
}

#endif