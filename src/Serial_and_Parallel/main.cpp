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

void Compare_Normal_k_means(vector<vector<double>> data, const bool webmode, char mode);
char getMode(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	srand(time(NULL));
	vector<vector<double>> data;

	bool webmode = false;

        int DataSize(atoi(argv[1]));
        int Dimensions(atoi(argv[2]));
        int Max(atoi(argv[3]));
        int Min(atoi(argv[4]));

	char mode = getMode(argc, argv);
        data = generate2DData(DataSize, Dimensions, Max, Min);

	Compare_Normal_k_means(Normalize_Data(data), webmode, argv[5][0]);
}

char getMode(int argc, char* argv[]){
	if(argc > 5) return argv[5][0];
	else return 'S';
}

void Compare_Normal_k_means(vector<vector<double>> data, const bool webmode, char mode)
{
	bool result;
	double start = omp_get_wtime();
		if(toupper(mode) == 'S') result = k_Means(data, webmode);
		else result = parallel_k_Means(data, webmode);
	double end = omp_get_wtime();
	
	cout << end-start << endl;
    
}
