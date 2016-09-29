/*
	This code is a parallel version of k-means. Input is assumed to be normalized.
	The parallelization occurs from the datapoints perspective. i.e. Whenever the datapoints are looped over it is done in parallel. There is potential for nested parallelism and parallelizing parts from the cluster perspective however the overhead is assumed to be too much for the time being until further testing is done.
*/

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <fstream>
#include "omp.h"

using namespace std;

char DEFAULT_FILE[] = "Test.txt";

typedef struct{
	double* centre;
	double* sumPoints;
	double SSE;
	int numPoints;
}cluster;

//Get parameters from command line
char* getFileName(int argc, char* argv[]);
int getNumClusters(int argc, char* argv[]);

//Extract info from file
int getNumLines(char* fileName);
int getDimension(char* fileName, char separator);

//Init functions (only ever doing malloc)
cluster* initClusters(int numClusters, int dimension);
double** initMatrix(int numLines);

//Extract datapoints from text file
void extractDatapoints(double** matrix, char* fileName, char separator, int dimension);
	double* extractDatapoint(string line, char separator, int dimension);

//Print functions
void printMatrix(double** matrix, int rows, int columns);
void printClusterCentres(cluster* clusters, int numClusters, int dimension);
void printArray(double* array, int arrayLength);

//Initializing and randomizing clusters
cluster* generateClusterCentres(int numClusters, int dimension);

//K-means functions
double calcEuclidDist(double* a, double* b, int dimension);
double* euclidPerCluster(cluster* clusters, double* datapoint, int numClusters, int dimension);
int getMinIndex(double* array, int arrayLength);
void kmeans(cluster* clusters, double** data, int numClusters, int dimension, int numPoints);
void moveClusters(cluster* clusters, int numClusters, int dimension);
double calcSSE(cluster* clusters, int numClusters);

//For timing
double start;
void startTimer();
double getRuntime();

int main(int argc, char* argv[]){
	//Get file name
	char* fileName = getFileName(argc, argv);

	//Get information on data
	int dimension = getDimension(fileName, ' ');
	int numLines = getNumLines(fileName);

	//Initialize 2D array to store data
	double** data = initMatrix(numLines);

	//Read datapoints from text file
	extractDatapoints(data, fileName, ' ', dimension);

	//Get number of clusters to use
	int numClusters = getNumClusters(argc, argv);

	//Generate random cluster centres
	cluster* clusters = generateClusterCentres(numClusters, dimension);

	//Variable to keep while loop running while clustering is improving
	int smallChangeCount = 0;
	double lastSSE = 999;

	startTimer();
	while(smallChangeCount < 5){
		kmeans(clusters, data, numClusters, dimension, numLines);
		moveClusters(clusters, numClusters, dimension);
		if(lastSSE - calcSSE(clusters, numClusters) < 0.001){
			smallChangeCount++;
		}
		lastSSE = calcSSE(clusters, numClusters);
		//cout << lastSSE << endl;
	}
	cout << getRuntime() << endl;
}

//Start timer using global variable "start"
void startTimer(){
	start = omp_get_wtime();
}

//Returns run time from call to startTimer() to this function call
double getRuntime(){
	return omp_get_wtime() - start;
}

//Sums sum of squares error for each cluster
double calcSSE(cluster* clusters, int numClusters){
	double totalSSE = 0;

	for(int i = 0; i < numClusters; i++){
		totalSSE += clusters[i].SSE;
	}

	return totalSSE;
}

//Finish average calculation and move cluster centres
void moveClusters(cluster* clusters, int numClusters, int dimension){
	for(int i = 0; i < numClusters; i++){
		for(int j = 0; j < dimension; j++){
			clusters[i].centre[j] = clusters[i].sumPoints[j]/(double)clusters[i].numPoints;
		}
	}
}

//Iterate through datapoints and assign them to clusters, calculating average along the way aka k-means
void kmeans(cluster* clusters, double** data, int numClusters, int dimension, int numPoints){
	//Reset counters for each cluster, may be beneficial to parallelize
	for(int i = 0; i < numClusters; i++){
		clusters[i].numPoints = 0;
		clusters[i].SSE = 0;
		for(int k = 0; k < dimension; k++){
			clusters[i].sumPoints[k] = 0;
		}
	}

	#pragma omp parallel for shared(clusters, data)
	for(int i = 0; i < numPoints; i++){
		double* distances = euclidPerCluster(clusters, data[i], numClusters, dimension);
		int assignedCluster = getMinIndex(distances, numClusters);
		clusters[assignedCluster].numPoints++;
		for(int j = 0; j < dimension; j++){
			clusters[assignedCluster].sumPoints[j] += data[i][j];
			clusters[assignedCluster].SSE = pow(distances[assignedCluster],2);
		}
	}
}

//Return index of min element in array of doubles
int getMinIndex(double* array, int arrayLength){
	double min = array[0];
	int minIndex = 0;

	for(int i = 1; i < arrayLength; i++){
		if(array[i] < min){
			minIndex = i;
			min = array[i];
		}
	}

	return minIndex;
}

//Calculate Euclidean distance for a datapoint for each cluster centre
double* euclidPerCluster(cluster* clusters, double* datapoint, int numClusters, int dimension){
	double* distances = (double*) malloc(sizeof(double)*numClusters);

	for(int i = 0; i < numClusters; i++){
		distances[i] = calcEuclidDist(clusters[i].centre, datapoint, dimension);
	}

	return distances;
}

//Calculate Euclidean distance
double calcEuclidDist(double* a, double* b, int dimension){
	double result = 0;

	for(int i = 0; i < dimension; i++){
		result += pow((a[i] - b[i]), 2);
	}

	return sqrt(result);
}

//Initialize array of clusters and generate cluster centres in range [0,1] in parallel
cluster* generateClusterCentres(int numClusters, int dimension){
	//Initialize array of clusters
	cluster* clusters = initClusters(numClusters, dimension);

	#pragma omp parallel for
	for(int i = 0; i < numClusters; i++){
		clusters[i].centre = (double*) malloc(sizeof(double)*dimension);
		clusters[i].sumPoints = (double*) malloc(sizeof(double)*dimension);

		for(int j = 0; j < dimension; j++){
			clusters[i].centre[j] = (rand()/(double) RAND_MAX);
			clusters[i].sumPoints[j] = 0;
		}
	}

	return clusters;
}

//Print cluster centres
void printClusterCentres(cluster* clusters, int numClusters, int dimension){
	for(int i = 0; i < numClusters; i++){
		for(int j = 0; j < dimension; j++){
			cout << clusters[i].centre[j] << " ";
		}
		cout << endl;
	}
	
}

//Print 2D matrix
void printMatrix(double** matrix, int rows, int columns){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			cout << matrix[i][j] << " ";
		}

		cout << endl;
	}
}

void printArray(double* array, int arrayLength){
	for(int i = 0; i < arrayLength; i++){
		cout << array[i] << " ";
	}
}

//Extract datapoints from text file
void extractDatapoints(double** matrix, char* fileName, char separator, int dimension){
	ifstream dataFile(fileName);
	string line;
	int index = 0;

	if(dataFile.is_open()){
		while(getline(dataFile, line)){
			matrix[index] = extractDatapoint(line, separator, dimension);
			index++;
		}
	}
}

//Extract a single datapoint from a string
double* extractDatapoint(string line, char separator, int dimension){
	double* datapoint = (double*) malloc(sizeof(double)*dimension);
	string currSubstring = line;
	int currPosition;
	int index = 0;

	while(index != dimension){
		currPosition = currSubstring.find(separator);
		datapoint[index] = strtod(currSubstring.substr(0, currPosition).c_str(), NULL);
		index++;
		currSubstring = currSubstring.substr(currPosition+1);
	}

	return datapoint;
}

//Get file name from command line parameters
char* getFileName(int argc, char* argv[]){
	if(argc > 1) return  argv[1];
	else return DEFAULT_FILE;
}

//Get number of clusters to use from command line parameters 15 is default
int getNumClusters(int argc, char* argv[]){
	if(argc > 2) return strtol(argv[2],NULL, 10);
	else return 15;
}

//Initialize array of clusters as well as the sumPoints field
cluster* initClusters(int numClusters, int dimension){
	cluster* clusters = (cluster*) malloc(numClusters*(sizeof(double*)*2+sizeof(double)*2));	//malloc'd like this due to seg fault (I presume due to sizeof(cluster) returning incorrect value due to inner malloc being required, better work around may be available).
	
	for(int i = 0; i < numClusters; i++){
		clusters[i].sumPoints = (double*) malloc(sizeof(double)*dimension);

		for(int j = 0; j < dimension; j++){
			clusters[i].sumPoints[j] = 0;
		}
	}
	
	return clusters;
}

//Initialize 2D array for storing dataPoints
double** initMatrix(int numLines){
	double** matrix = (double**) malloc(sizeof(double*)*numLines);

	return matrix;
}

//Returns number of lines in file
int getNumLines(char* fileName){
	ifstream dataFile(fileName);
	string line;
	int numLines = 0;

	if(dataFile.is_open()){
		while(getline(dataFile, line)){
			numLines++;
		}
	}

	dataFile.close();

	return numLines;
}

//Returns dimension of first line in file
int getDimension(char* fileName, char separator){
	ifstream dataFile(fileName);
	string line;
	int dimension = 1; //One more dimension than the number of separators
	int pos = -1;

	if(dataFile.is_open()) getline(dataFile, line);

	pos = line.find(separator);
	while(pos != std::string::npos){
		dimension++;
		line = line.substr(pos + 1);
		pos = line.find(separator);
	}

	return dimension;
}
