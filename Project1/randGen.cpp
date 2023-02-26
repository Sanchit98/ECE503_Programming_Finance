#include "randGen.h"
#include <cmath>
#include <fstream>
using namespace std;


#define RANDGEN_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <sstream>
#include <stdlib.h>

#define RESET    "\033[0m"
#define BLACK    "\033[30m"
#define RED      "\033[31m"
#define GREEN    "\033[32m"
#define YELLOW   "\033[33m"
#define BLUE     "\033[34m"
#define MAGENTA  "\033[35m"
#define CYAN     "\033[36m"
#define WHITE    "\033[37m"
#define BOLDBLACK    "\033[1m\033[30m"
#define BOLDRED      "\033[1m\033[31m"
#define BOLDGREEN    "\033[1m\033[32m"
#define BOLDYELLOW   "\033[1m\033[33m"
#define BOLDBLUE     "\033[1m\033[34m"
#define BOLDMAGENTA  "\033[1m\033[35m"
#define BOLDCYAN     "\033[1m\033[36m"
#define BOLDWHITE    "\033[1m\033[37m"


//-------------------------------------------------

void DebugPrint::setDebugLevel (int dl){
	debugLevel = dl;
} 
  
int DebugPrint::getDebugLevel (){
	return debugLevel;
}    

void DebugPrint::print(int dL, std::string statement){

	if (dL < debugLevel) {
		return;
	}
	if (dL == 1) {
		cout << GREEN << "INFO: " << statement << RESET << endl;
	} else if (dL == 2) {
		cout << BOLDCYAN << "WARNING: " << statement << RESET << endl;
	} else if (dL == 3) {
		cout << YELLOW << "ERROR: " << statement << RESET << endl;
	} else if (dL == 4) {
		cout << MAGENTA << "SEVERE: " << statement << RESET << endl;
	} else if (dL == 5) {
		cout << BOLDRED << "FATAL: " << statement << RESET << endl;
		exit(EXIT_FAILURE);
	}  else {
		cout << "Sepecified debug level: " << dL << " is not defined in debugPrint function\n";
		exit(EXIT_FAILURE);
	}	
}



RandGen::RandGen(int rng, int ctr){
	range = rng;
	cntr = ctr;
}

int RandGen::getRange(){
	//display range to user
	return range;
}

void RandGen::setRange(int rng){
	//set range from user
	range = rng;
}

int RandGen::readCntr(){
	//read the center
	cout<<"Enter coordinate of center: "<<endl;
	cin>>cntr;
	cout<<endl;
	
	return cntr;
}

double* RandGen::genPoint(){
	//randomly generate the points
	double* pointer;
	point[0] = (double) rand()/range;
	point[1] = (double) rand()/range;
	pointer = point;
	return pointer;
}

double RandGen::distance(){
	double dist;
	
	dist = sqrt(pow((point[0]-cntr), 2) + pow((point[1]-cntr), 2));
	return dist;
}

void FindPi::setEstmResults(double estmResults){
	estimatedResults = estmResults;
}

double FindPi::getEstmResults(){
	return estimatedResults;
}

double FindPi::runEstimation(int itr, int randLimit){

	RandGen rgObj(randLimit);
	int circle_points = 0, square_points = 0;

	double *point_arr;
	double distance;
	
	ofstream file;
	file.open("project_1_points.txt");
	
	
	for(int i=0; i<itr; i++)
	{
		point_arr = rgObj.genPoint();
		
		file << *point_arr<<"\t"<<*(point_arr+1)<<"\n";
		
		
		//Check if point is in circle byb calculating distance
		distance = rgObj.distance();
		
		if(distance<=1)
		{
			circle_points++;
		}
		square_points++;
		
	}
	
	 setEstmResults(4*double(circle_points/(double)square_points));
	 return estimatedResults;
}

