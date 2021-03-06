#ifndef TEST_DATA_HELPER
#define TEST_DATA_HELPER

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <time.h>
#include <list>
#include <fstream>
#include "omp.h"
 
using namespace std;

vector<vector<double>> getData();
vector<vector<double>> generate2DData(int dataSize, int dimensions, double max, double min);

vector<vector<double>> getData()
{
	return 
	{
    	{ 5.1, 3.5 }, { 4.9, 3.0 }, { 4.7, 3.2 }, { 4.6, 3.1 }, { 5.0, 3.6 }, { 5.4, 3.9 }, { 4.6, 3.4 }, { 5.0, 3.4 }, { 4.4, 2.9 }, { 4.9, 3.1 }, { 5.4, 3.7 }, { 4.8, 3.4 }, { 4.8, 3.0 }, { 4.3, 3.0 }, { 5.8, 4.0 }, { 5.7, 4.4 }, { 5.4, 3.9 }, { 5.1, 3.5 }, { 5.7, 3.8 }, { 5.1, 3.8 }, { 5.1, 3.5 }, { 4.9, 3.0 }, { 4.7, 3.2 }, { 4.6, 3.1 }, { 5.0, 3.6 }, { 5.4, 3.9 }, { 4.6, 3.4 }, { 5.0, 3.4 }, { 4.4, 2.9 }, { 4.9, 3.1 }, { 5.4, 3.7 }, { 4.8, 3.4 }, { 4.8, 3.0 }, { 4.3, 3.0 }, { 5.8, 4.0 }, { 5.7, 4.4 }, { 5.4, 3.9 }, { 5.1, 3.5 }, { 5.7, 3.8 }, { 5.1, 3.8 }, { 5.1, 3.5 }, { 4.9, 3.0 }, { 4.7, 3.2 }, { 4.6, 3.1 }, { 5.0, 3.6 }, { 5.4, 3.9 }, { 4.6, 3.4 }, { 5.0, 3.4 }, { 4.4, 2.9 }, { 4.9, 3.1 }, { 5.4, 3.7 }, { 4.8, 3.4 }, { 4.8, 3.0 }, { 4.3, 3.0 }, { 5.8, 4.0 }, { 5.7, 4.4 }, { 5.4, 3.9 }, { 5.1, 3.5 }, { 5.7, 3.8 }, { 5.1, 3.8 }, { 5.1, 3.5 }, { 4.9, 3.0 }, { 4.7, 3.2 }, { 4.6, 3.1 }, { 5.0, 3.6 }, { 5.4, 3.9 }, { 4.6, 3.4 }, { 5.0, 3.4 }, { 4.4, 2.9 }, { 4.9, 3.1 }, { 5.4, 3.7 }, { 4.8, 3.4 }, { 4.8, 3.0 }, { 4.3, 3.0 }, { 5.8, 4.0 }, { 5.7, 4.4 }, { 5.4, 3.9 }, { 5.1, 3.5 }, { 5.7, 3.8 }, { 5.1, 3.8 }, { 5.1, 3.5 }, { 4.9, 3.0 }, { 4.7, 3.2 }, { 4.6, 3.1 }, { 5.0, 3.6 }, { 5.4, 3.9 }, { 4.6, 3.4 }, { 5.0, 3.4 }, { 4.4, 2.9 }, { 4.9, 3.1 }, { 5.4, 3.7 }, { 4.8, 3.4 }, { 4.8, 3.0 }, { 4.3, 3.0 }, { 5.8, 4.0 }, { 5.7, 4.4 }, { 5.4, 3.9 }, { 5.1, 3.5 }, { 5.7, 3.8 }, { 5.1, 3.8 }, { 5.1, 3.5 }, { 4.9, 3.0 }, { 4.7, 3.2 }, { 4.6, 3.1 }, { 5.0, 3.6 }, { 5.4, 3.9 }, { 4.6, 3.4 }, { 5.0, 3.4 }, { 4.4, 2.9 }, { 4.9, 3.1 }, { 5.4, 3.7 }, { 4.8, 3.4 }, { 4.8, 3.0 }, { 4.3, 3.0 }, { 5.8, 4.0 }, { 5.7, 4.4 }, { 5.4, 3.9 }, { 5.1, 3.5 }, { 5.7, 3.8 }, { 5.1, 3.8 }, { 5.1, 3.5 }, { 4.9, 3.0 }, { 4.7, 3.2 }, { 4.6, 3.1 }, { 5.0, 3.6 }, { 5.4, 3.9 }, { 4.6, 3.4 }, { 5.0, 3.4 }, { 4.4, 2.9 }, { 4.9, 3.1 }, { 5.4, 3.7 }, { 4.8, 3.4 }, { 4.8, 3.0 }, { 4.3, 3.0 }, { 5.8, 4.0 }, { 5.7, 4.4 }, { 5.4, 3.9 }, { 5.1, 3.5 }, { 5.7, 3.8 }, { 5.1, 3.8 }, { 5.1, 3.5 }, { 4.9, 3.0 }, { 4.7, 3.2 }, { 4.6, 3.1 }, { 5.0, 3.6 }, { 5.4, 3.9 }, { 4.6, 3.4 }, { 5.0, 3.4 }, { 4.4, 2.9 }, { 4.9, 3.1 }, { 5.4, 3.7 }, { 4.8, 3.4 }, { 4.8, 3.0 }, { 4.3, 3.0 }, { 5.8, 4.0 }, { 5.7, 4.4 }, { 5.4, 3.9 }, { 5.1, 3.5 }, { 5.7, 3.8 }, { 5.1, 3.8 }
	};
}

vector<vector<double>> generate2DData(int dataSize, int dimensions, int max, int min)
{
	srand(time(NULL));
	vector<vector<double>> dataSet(dataSize, std::vector<double>(dimensions));

	for (int i = 0; i < dataSize; i++)
	{
		for (int j = 0; j < dimensions; j++)
		{
			dataSet[i][j] = rand() % max + min;
		}
	}

	return dataSet;
}

#endif