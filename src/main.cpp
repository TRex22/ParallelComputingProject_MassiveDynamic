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
	//index 0 is raw console out
	//index 1 is nice stringified json for webui
	vector<string> output = {"", ""};
	vector<string> serial_out = {"", "serial: {"};
	vector<string> parallel_out = {"", "parallel: {"};

	output[0] += "*********************SERIAL*********************\n";
    double serial_start = omp_get_wtime();
    	serial_out = k_Means(data, webmode);
    double serial_end = omp_get_wtime();
    output[0] += serial_out[0];
    


	output[0] += "*********************PARALLEL*********************\n";
    double parallel_start = omp_get_wtime();
    	parallel_out = parallel_k_Means(data, webmode);
    double parallel_end = omp_get_wtime();
    output[0] += parallel_out[0];



    double serial_time = serial_end - serial_start;
    double parallel_time = parallel_end - parallel_start;

    output[0] += "Serial time: " + to_string(serial_time) + "\n";
    output[0] += "Parallel time: " + to_string(parallel_time) + "\n"; 

    serial_out[1] += "\"time\": " + to_string(serial_time) + "}";
    parallel_out[1] += "\"time\": " + to_string(parallel_time) + "}";

	output[1] += serial_out[1] + ", ";
    output[1] += parallel_out[1];

    if(serial_time <= parallel_time)
    {
    	output[0] += "Serial faster :(\n";
    }
    else
    {
    	output[0] += "Parallel faster :)\n";
    }

    if (!webmode)
    {
    	//print console
    	cout << output[0] << endl;
    }
    else if (webmode)
    {
    	//print json
    	cout << output[1] << endl;
    }
}