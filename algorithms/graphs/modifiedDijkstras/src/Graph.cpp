/****************************************************************
 *   File: Graph.cpp
 *   Author: Robert Grossman
 *   Created on: December 6, 2014
 *   E-mail: rgross1@umbc.edu
 * 
 *  This file contains the implementation for the Graph class that is used
 * to read in the data from an input file, create a representation of the
 * related graph, and find the minimum number of trips required to move the
 * tourists from the specified start city to the specified destination city.
 * 
 ****************************************************************/

#include "Graph.h"

Graph::Graph(string fileName)
{
	ifstream input;
	input.open(fileName.c_str(), ifstream::in);
	string token = "";
	input >> token; //the first one's the number of vertexes
	size = atoi(token.c_str()) + 1; //the number of vertexes becomes the size of the adjacency matrix plus 1 for 0 indexing
	graph = new int*[size];
	for (int i = 0; i < size; i++)	
	{
		graph[i] = new int[size];
		for (int j = 0; j < size; j++) 
		{
			graph[i][j] = 0;
		}
	}

	//need to store the number of edges
	input >> token;
	
	do
	{
		input >> token;
		int row = atoi(token.c_str());
		input >> token;
		int col = atoi(token.c_str());
		input >> token;
		int weight = atoi(token.c_str());
		if (row < size && col < size) 
		{
		graph[row][col] = weight;
		graph[col][row] = weight;
		}
	}
	while (!input.eof());
	
	//need to close the stream
	input.close();

}

Graph::~Graph()
{
	for (int i = 0; i < size; i++) 
	{
		delete [] graph[i];
		graph[i] = NULL;
	}	
	delete [] graph;
	graph = NULL;
}

int Graph::trips(int source, int destination, int tourists)
{

	queue<int> vertices;
	bool* visited = new bool[size];
	int* maxMin = new int[size];
	
	//initialize the visited and maximum-minimum arrays
	for (int i = 0; i < size; i++) 
	{
		visited[i] = false;
		maxMin[i] = 0;
	}  

	vertices.push(source);

	//using breadth first search
	while (!vertices.empty()) {
		//get the first element in the queue
		int currentVertex = vertices.front();
		//set that element to visited so that we don't repeat ourselves
		visited[currentVertex] = true;

		for (int i = 0; i < size; i++) 
		{	
			//if there is an actual connection at from the two vertices
			if (graph[currentVertex][i] != 0 && !visited[i]) 
			{
				vertices.push(i);
				int val = graph[currentVertex][i];
				
				//make the current value equal to the previous minMax value if it's greater
				if (maxMin[currentVertex] < val && maxMin[currentVertex] != 0) 
				{	
					val = maxMin[currentVertex];
				}
				
				//make the current minMax value equal to the current value if it's smaller
				if (val > maxMin[i]) 
				{
					maxMin[i] = val;
				}
			}  
		}
		
		vertices.pop();	
	}

	int maxBottleneck = maxMin[destination] - 1; //subtract one for the driver
	int trips = 0;
	int capacity = 0;
	
	//calculate how many trips it will take given the current max bottleneck value
	while (capacity < tourists)
	{
		trips++;
		capacity += maxBottleneck;
	}

	//free-up all the dynamic memory used in this method
	delete [] visited;
	visited = NULL;
	delete [] maxMin;
	maxMin = NULL;
	
	return trips;
}
