/* By default uses range [0,1].
	Range will be added as input parameter at a later date along with better parameter handling.
	^^Done if we decide to add normalization to project.
	Currently if only one parameter is given it is used as numPoints.
	No parameters given means default 3 dimensions and 50 points.
	ie first parameter is numpoints, second is dimension.
*/

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>

using namespace std;

const int DEFAULT_NUMPOINTS = 50;
const int DEFAULT_DIMENSION = 3;
const int DEFAULT_MIN = 0;
const int DEFAULT_MAX = 1;

int getDimension(int argc, char* argv[]);
int getNumPoints(int argc, char* argv[]);

void doRandom(int dim, int num, int min, int max);

int main(int argc, char* argv[]){

	int numPoints = getNumPoints(argc, argv);
	int dimension = getDimension(argc, argv);
	
	if(dimension == 0){
		cout << "Using default dimension (" << DEFAULT_DIMENSION << ")" << endl;
		dimension = DEFAULT_DIMENSION;
	}
	
	if(numPoints == 0){
		cout << "Using default number of points (" << DEFAULT_NUMPOINTS << ")" << endl;
		numPoints = DEFAULT_NUMPOINTS;
	}

	doRandom(dimension, numPoints, DEFAULT_MIN, DEFAULT_MAX);
		
		
}

void doRandom(int dim, int num, int min, int max){
	srand(time(NULL));
	
	for(int i = 0; i < num; i++){
		for(int j = 0; j < dim; j++){
			cout << min + ((rand()/(double)RAND_MAX) * (max-min));
			if(j != dim-1){
				cout << " ";
			} 
		}
		cout << endl;
	}
}

int getNumPoints(int argc, char* argv[]){
	if(argc < 2){
		return 0;
	}
	return strtol(argv[1], NULL, 10);
}

int getDimension(int argc, char* argv[]){
	if(argc < 3){
		return 0;
	}
	return strtol(argv[2], NULL, 10);
}




