#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <time.h>
#include <list>
#include <fstream>
#include "omp.h"

//include modules
#include "k_means.cpp"
#include "test_data_helper.cpp"

using namespace std;

vector<vector<double>> extractDatapoints(char* fileName, char separator);
vector<double> extractDatapoint(string line, char separator);

void k_means(vector<vector<double>> data, char mode, int clusters, bool eval);
char getMode(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	vector<vector<double>> data;


	char mode = getMode(argc, argv);
        data = extractDatapoints(argv[2], ' ');

	if( (argc > 4) && (toupper(argv[4][0]) == 'E') )	k_means(Normalize_Data(data), argv[1][0], strtol(argv[3], NULL, 10), true);
	else	k_means(Normalize_Data(data), argv[1][0], strtol(argv[3], NULL, 10), false);
}

//Extract datapoints from text file
vector<vector<double>> extractDatapoints(char* fileName, char separator){
	ifstream dataFile(fileName);
	string line;
	vector<vector<double>> matrix;

	if(dataFile.is_open()){
		while(getline(dataFile, line)){
			matrix.push_back(extractDatapoint(line, separator));
		}
	}
	
	return matrix;
}

//Extract a single datapoint from a string
vector<double> extractDatapoint(string line, char separator){
	vector<double> datapoint;
	string currSubstring = line;
	int currPosition = 0;

	while(currPosition != string::npos){
		currPosition = currSubstring.find(separator);
		datapoint.push_back(strtod(currSubstring.substr(0, currPosition).c_str(), NULL));
		currSubstring = currSubstring.substr(currPosition+1);	
	}

	return datapoint;
}

//Extract run mode from argv (p=parallel or s=serial)
char getMode(int argc, char* argv[]){
	if(argc > 5) return argv[5][0];
	else return 'S';
}

void k_means(vector<vector<double>> data, char mode, int clusters, bool eval)
{
	bool result;
	double start = omp_get_wtime();
		if(toupper(mode) == 'S') result = k_Means(data, clusters, eval);
		else result = parallel_k_Means(data, clusters, eval);
	double end = omp_get_wtime();
	
	if(!eval) cout << end-start;
    
}
