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

void Print_Data(vector< vector<double> > data);
void Print_Data(vector<double> data);
void Print_Data(vector<int> data);

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

#endif