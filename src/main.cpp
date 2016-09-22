#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <time.h>
#include <list>
#include <fstream>
#include "omp.h"

//include modules
#include "k_means_online.cpp"
#include "k_means.cpp"
#include "test_data_helper.cpp"
/*#include "maths_helpers.cpp"
#include "print_helper.cpp"*/

using namespace std;

void Compare_Normal_k_means(vector<vector<double>> data, const bool webmode);
void Console_Compare_Out(vector<vector<double>> data, const bool webmode);

int main(int argc, char* argv[])
{
	srand(time(NULL));

	//TODO: make random data possible
	vector<vector<double>> data = getData();

	bool webmode = false;
	if (argc == 2)
	{
		string arg(argv[1]);
		if (arg == "webmode" || arg == "true" || arg == "on")
		{
			webmode = true;
		}
	}

	Compare_Normal_k_means(Normalize_Data(data), webmode);
}

void Compare_Normal_k_means(vector<vector<double>> data, const bool webmode)
{
	if (webmode)
	{
		k_Means(data, webmode);
		parallel_k_Means(data, webmode);
	}
	else if (!webmode)
	{
		Console_Compare_Out(data, webmode);
	}
}

void Console_Compare_Out(vector<vector<double>> data, const bool webmode)
{
	cout << "*********************SERIAL*********************" << endl;
    double serial_start = omp_get_wtime();
    	k_Means(data, webmode);
    double serial_end = omp_get_wtime();

    cout << "*********************PARALLEL*********************" << endl;
    double parallel_start = omp_get_wtime();
    	parallel_k_Means(data, webmode);
    double parallel_end = omp_get_wtime();

    cout << "Serial time: " << serial_end - serial_start << endl;
    cout << "Parallel time: " << parallel_end - parallel_start << endl;  

    if(serial_end - serial_start <= parallel_end - parallel_start)
    {
    	cout << "Serial faster :(" << endl;
    }
    else
    {
    	cout << "Parallel faster :)" << endl;
    }
}