#ifndef PRINT_HELPER
#define PRINT_HELPER

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <time.h>
#include <list>
#include <fstream>
#include "omp.h"
 
using namespace std;

void Print_Data(const string message, vector<vector<double>> data);
void Print_Data(const string message, vector<double> data);
void Print_Data(const string message, vector<int> data);
void Print_Data(const string message, int data);
void Print_Data(const string message, double data);
void Print_Data(const string message);
void Print_File(const string file, vector<double> centres);

void Print_Data(const string message, vector<vector<double>> data)
{
    cout << message << endl;
    for(int i = 0;i < data.size();i++){
    	for (int j = 0; j < data[0].size(); ++j)
    	{
    		cout << data[i][j] << " ";
    	}
    	cout <<  endl;
    }
    cout <<  endl;
}

void Print_Data(const string message, vector<double> data)
{
    cout << message << endl;
    for(int i = 0;i < data.size();i++){
    	cout << data[i] << " ";
    }
    cout <<  endl;
}

void Print_Data(const string message, vector<int> data)
{
    cout << message << endl;
    for(int i = 0;i < data.size();i++){
    	cout << data[i] << " ";
    }
    cout <<  endl;
}

void Print_Data(const string message, int data)
{
    cout << message << data << endl;
}

void Print_Data(const string message, double data)
{
    cout << message << data << endl;
}

void Print_Data(const string message)
{
    cout << message << endl;
}

void Print_File(const string filename, vector<vector<double>> centres)
{   
    ofstream file;
    //Opens a file and prints the cluster centres in a csv format to plug into excel
    file.open(filename, ios::app);
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

#endif