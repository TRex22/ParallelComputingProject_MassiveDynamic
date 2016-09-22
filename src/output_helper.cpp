#ifndef OUTPUT_HELPER
#define OUTPUT_HELPER

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <time.h>
#include <list>
#include <fstream>
#include "omp.h"
 
using namespace std;

string wrap_output(string kmeans, string online_kmeans);
vector<string> Get_Data(vector<string> output, const string message, vector<vector<double>> data);
vector<string> Get_Data(vector<string> output, const string message, int data);
vector<string> Get_Data(vector<string> output, const string message, double data);
vector<string> Get_Data(vector<string> output, const string message);

string wrap_output(string kmeans, string online_kmeans)
{
	string output = "{";
	output += kmeans + ", " + online_kmeans;
	output += " }";

	return output;
}

vector<string> Get_Data(vector<string> output, const string message, vector<vector<double>> data)
{
    output[0] += "" + message + ": " + "\n";
    output[1] += "\"" + message + "\": [";

    for(int i = 0; i < data.size(); i++){
    	output[1] += "{";
    	for (int j = 0; j < data[0].size(); ++j)
    	{
    		output[0] += to_string(data[i][j]) + " ";
    		if (j != data[0].size() - 1)
    		{
    			output[1] += "\"" + to_string(data[i][j]) + "\",";
    		}
    		else
    		{
    			output[1] += "\"" + to_string(data[i][j]) + "\"";
    		}    		
    	}
    	output[0] += "\n";
    	output[1] += "},\n";
    }

    output[0] += "\n";
    output[1] += "],\n";

    return output;
}

vector<string> Get_Data(vector<string> output, const string message, int data)
{
	output[0] += "" + message + ": " + to_string(data) + "\n";
    output[1] += "\"" + message + "\": \"" + to_string(data) + "\",";

    return output;
}

vector<string> Get_Data(vector<string> output, const string message, double data)
{
    output[0] += "" + message + ": " + to_string(data) + "\n";
    output[1] += "\"" + message + "\": \"" + to_string(data) + "\",\n";

    return output;
}

vector<string> Get_Data(vector<string> output, const string message)
{
    output[0] += "" + message + "\n";
    /*output[1] += ;*/

    return output;
}

#endif