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
/*#include "maths_helpers.cpp"
#include "print_helper.cpp"*/

using namespace std;

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


	k_Means_Online(data); //Calls k-means

	//Opens a file and prints the normalized data in a csv format to plug into excel
	ofstream file;
	file.open("normal_data.csv");
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