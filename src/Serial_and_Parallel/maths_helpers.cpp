#ifndef MATHS_HELPER
#define MATHS_HELPER

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <time.h>
#include <list>
#include <fstream>
#include "omp.h"
 
using namespace std;

double Mean_Squared_Error(vector< vector<double> > data, vector< vector<double> > centres);
double Find_Min(vector<double> data);
double Find_Distance(vector<double> data, vector<double> centres);
void Normalize_StdDeviation(vector< vector<double> > &data, int column);
vector< vector<double> > Normalize_Data(vector< vector<double> > data);

//Only works for normal k-means
double Mean_Squared_Error(vector< vector<double> > data, vector< vector<double> > centres){
	double sum = 0;

	for (int j = 0; j < centres.size(); ++j){
		for (int i = 0; i < data.size(); ++i){
			for (int k = 0; k < data[0].size(); ++k){
				sum += pow(data[i][k] - centres[j][k], 2);
			}
		}
	}

	return sum;
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

//Normalizes the data using the std deviation method.
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

vector< vector<double> > Normalize_Data(vector< vector<double> > data){
	for (int i = 0; i < data[0].size(); ++i)
	{
		Normalize_StdDeviation(data, i);
	}

	return data;
}

#endif