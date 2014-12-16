#include "Graph.h"
#include <iostream>
using namespace std;
int main(int argc, char *argv[]) {
	cout << "Driver::Here0" << endl;
	//read the command line argument and generate a graph
	string filename = argv[1];
	cout << "Driver::Here1" << endl;
	Graph mygraph(filename);
	cout << "Driver::Here2" << endl;
	int s, d, t;
	//take user input on the source city, destination city, and the number of tourists
	cin>> s >> d >> t;
	//print the minimum number of trips
	cout<<"Minimum Number of Trip: "<<mygraph.trips(s,d,t) <<endl;
	return 0;
}

