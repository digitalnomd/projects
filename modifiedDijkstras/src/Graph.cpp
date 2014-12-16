#include "Graph.h"

Graph::Graph(string fileName)
{
	ifstream input;
	input.open(fileName.c_str(), ifstream::in);
	string token = "";
	input >> token; //the first one's the number of vertexes
	size = atoi(token.c_str()) + 1; //the number of vertexes becomes the size of the adjacency matrix plus 1 for 0 indexing
	graph = new int*[size];
	cout << "Graph::Here1" << endl;
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
	
	cout << "Graph::Here2" << endl;
	do
	{
		cout << "Graph::Here3" << endl;
		input >> token;
		int row = atoi(token.c_str());
		input >> token;
		int col = atoi(token.c_str());
		input >> token;
		int weight = atoi(token.c_str());
		cout << "Row: " << row << " Col: " << col << " Weight: " << weight << endl;
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
				if (maxMin[currentVertex] < val && maxMin[currentVertex] != 0) 
				{	
					val = maxMin[currentVertex];
				}
				
				if (val > maxMin[i]) 
				{
					maxMin[i] = val;
				}
			}  
		}
		
		vertices.pop();	
	}
	int maxBottleneck = maxMin[destination] - 1; //subtract one for the driver
	cout << "Max bottleneck: "<< maxBottleneck << endl;
	int trips = 0;
	int capacity = 0;
	while (capacity < tourists)
	{
		trips++;
		capacity += maxBottleneck;
	}

	delete [] visited;
	visited = NULL;
	delete [] maxMin;
	maxMin = NULL;
	
	return trips;
}
