/****************************************************************
 *   File: Graph.h
 *   Project: 5
 *   Author: Robert Grossman
 *   Created on: December 6, 2014
 *   Section: 03
 *   E-mail: rgross1@umbc.edu
 * 
 *   This file contains the interface for the Graph class that is used
 *  to read in the data from an input file, create a representation of the
 *  related graph, and find the minimum number of trips required to move the
 *  tourists from the specified start city to the specified destination city.
 * 
 * ****************************************************************/
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <cstdlib>
using namespace std;

class Graph {

public:
	/**********************************************************************
	 * Name: Graph (constructor)
	 * PreCondition: fileName -- name of the file whose contents are to be read in
	 * PostCondition:  Initializes an adjacency matrix with the contents from the given file.
	 **********************************************************************/
	Graph(string fileName);

	/**********************************************************************
 	* Name: Graph (destructor)
 	* PreCondition: None.
 	* PostCondition:  Free’s up the dynamic memory associated with the Graph object (i.e. the adjacency matrix.
 	***********************************************************************/
	~Graph();

	/**********************************************************************
 	* Name: trips
 	* PreCondition: source —- the starting vertex
	* destination —- the end vertex
	* tourists —- the number of tourists on the trip
 	* PostCondition:  Find’s the minimum number of trips from the source to the end given the number of tourists
	* on the trip.
 	***********************************************************************/
	int trips(int source, int destination, int tourists);

private:
	int** graph;	
	int size;


};

#endif
