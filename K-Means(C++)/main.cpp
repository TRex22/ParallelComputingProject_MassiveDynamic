#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <time.h>
#include <list>
#include <fstream>
#include "omp.h"
 
using namespace std;

void k_Means(vector< vector<double> > data);
double Find_Min(vector<double> data);
double Find_Distance(vector<double> data, vector<double> centres);
void Normalize_StdDeviation(vector< vector<double> > &data, int column);
void Print_Data(vector< vector<double> > data);
void Print_Data(vector<double> data);
void Print_Data(vector<int> data);
 
int main(){
	//srand(time(NULL));

	vector< vector<double> > data = {  {5.1,3.5},
										{4.9,3.0},
										{4.7,3.2},
										{4.6,3.1},
										{5.0,3.6},
										{5.4,3.9},
										{4.6,3.4},
										{5.0,3.4},
										{4.4,2.9},
										{4.9,3.1},
										{5.4,3.7},
										{4.8,3.4},
										{4.8,3.0},
										{4.3,3.0},
										{5.8,4.0},
										{5.7,4.4},
										{5.4,3.9},
										{5.1,3.5},
										{5.7,3.8},
										{5.1,3.8}	};


	for (int i = 0; i < data[0].size(); ++i)
	{
		Normalize_StdDeviation(data, i);
	}

	k_Means(data); //Calls k-means



//Opens a file and prints the normalized data in a csv format to plug into excel
	ofstream file;
	file.open("normal_data.csv", ios::app);
	for(int i = 0;i < data.size();i++){
		file << data[i][0];
    	for (int j = 1; j < data[0].size(); ++j)
    	{
    		file << "," << data[i][j];
    	}
    	file <<  endl;
    }
    file.close();

}

void k_Means(vector< vector<double> > data){
	ofstream file;
	int k;
	
	k = rand()%10 + 1;
	vector< vector<double> > centres(k, vector<double>(2, 0));

	for (int i = 0; i < centres.size(); i++)     //Randomises the cluster centres
	{
		for (int j = 0; j < centres[0].size(); j++)
		{
			centres[i][j] = ((double) rand() / (RAND_MAX));
		}
	}

	vector<int> clusters_assignment(data.size());
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
					cout << "data[" << i << "] is in cluster " << j << endl; 
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



			cout << "Mean of centre[" << j << "] is ";
			Print_Data(mean);
		}
		it++;
	}


	Print_Data(centres);

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
    file.close();

}


double Find_Min(vector<double> data){
	double min = data[0];
	for (int i = 1; i < data.size(); ++i)
	{
		if (data[i] < min)
		{
			min = data[i];
		}
	}
	return min;
}

double Find_Distance(vector<double> data, vector<double> centres){
	int closest_centre = 0;
	double distance = 0;
	for (int i = 0; i < data.size(); ++i)
	{
		distance += pow( (data[i] - centres[i]), 2 );
	}
	return sqrt(distance);
}

void Normalize_StdDeviation(vector< vector<double> > &data, int column){
	double mean = 0;
	double std_dev = 0;
	for (int i = 0; i < data.size(); ++i)
	{
		mean += data[i][column];
	}

	mean /= data.size();

	for (int i = 0; i < data.size(); ++i)
	{
		std_dev += pow((data[i][column]-mean), 2);
	}

	std_dev /= data.size();
	std_dev = sqrt(std_dev);

	for (int i = 0; i < data.size(); ++i)
	{
		data[i][column] = (data[i][column] - mean) / std_dev;
	}
}

void Print_Data(vector< vector<double> > data){
    for(int i = 0;i < data.size();i++){
    	for (int j = 0; j < data[0].size(); ++j)
    	{
    		cout << data[i][j] << " ";
    	}
    	cout <<  endl;
    }
    cout <<  endl;
}

void Print_Data(vector<double> data){
    for(int i = 0;i < data.size();i++){
    	cout << data[i] << " ";
    }
    cout <<  endl;
}

void Print_Data(vector<int> data){
    for(int i = 0;i < data.size();i++){
    	cout << data[i] << " ";
    }
    cout <<  endl;
}