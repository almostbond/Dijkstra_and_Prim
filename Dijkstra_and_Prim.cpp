// dijkstra_and_prim.cpp : This file contains the 'main' function. Program execution begins and ends there.

//Dijkstra code from https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/

//Prim code from https://www.geeksforgeeks.org/prims-algorithm-simple-implementation-for-adjacency-matrix-representation/

#include <vector>
#include <iostream>

using namespace std;
// Number of vertices in the graph 
#define V 9 
// fancy little thing I learned you dont need to include the size in the first spot if its a square matrix.
int graph[][V] = {  { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
					{ 4, 0, 8, 0, 0, 0, 0, 11, 0 },
					{ 0, 8, 0, 7, 0, 4, 0, 0, 2 },
					{ 0, 0, 7, 0, 9, 14, 0, 0, 0 },
					{ 0, 0, 0, 9, 0, 10, 0, 0, 0 },
					{ 0, 0, 4, 14, 10, 0, 2, 0, 0 },
					{ 0, 0, 0, 0, 0, 2, 0, 1, 6 },
					{ 8, 11, 0, 0, 0, 0, 1, 0, 7 },
					{ 0, 0, 2, 0, 0, 0, 6, 7, 0 } };



int minDistance(int dist[], bool sptSet[])
{
	// Initial min value set to "infinity"
	int min = INT_MAX, min_index;

	//iterates through the entirety of the graph.
	for (int v = 0; v < V; v++)
		//checks to see if a vertex has been visited and if the distance is less than the current minimum.
		//non adjacent nodes will 
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}


void printSolution(int dist[])
{
	cout << "Vertex \t\t Distance from Source\n";
	//converts from numbers into letters using the ascii decimal values.
	for (int i = 0; i < V; i++) {
		char c = 65 + i;
		cout << c << "\t\t" << dist[i] << endl;
	}
}


void dijkstra(int graph[V][V], int src)
{
	//List of distances w.r.t. (with respect to) some source node.
	int dist[V];

	//Nodes are only in this list if there value is equal to true otherwise they are treated as if they dont exist.	
	//Visited nodes will equal true otherwise the node will be false.
	bool sptSet[V]; 
	

	// Initializes all node distances to be infinite.
	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX, sptSet[i] = false;

	//source node is then initialized to be 0.
	dist[src] = 0;

	// Find shortest path for all vertices 
	for (int count = 0; count < V - 1; count++) {
		
		// finds the cheapest adjacent path w.r.t. the node currently being processed
		int u = minDistance(dist, sptSet);

		// said node is the marked as processed.
		sptSet[u] = true; 

		// Updates distance values of the adjacent nodes w.r.t. u. 
		for (int v = 0; v < V; v++)

			//checks to see if the node has already been processed.
			//checks to see if and edge exists i.e. dist < INT_MAX
			//checks to see if the sum of the current distance to that specific
			//node + the recently processed distance is less than the current listed distance.
			if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
				//if all of these statements are true, dist[v] is updated.
				dist[v] = dist[u] + graph[u][v];
	}

	// print the constructed distance array 
	printSolution(dist);
}


// quick fix that converts invalid edges from 0 to INT_MAX.
void graph_convert() {

	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			if (graph[i][j] == 0) {
				graph[i][j] = INT_MAX;
			}
		}
	}
}

// Returns true if edge u-v is a valid 
bool isValidEdge(int u, int v, vector<bool> inMST)
{
	if (u == v)//If the edge is a loop.
		return false;
	if (inMST[u] == false && inMST[v] == false)// if edge u-v is apart of the MST.
		return false;
	else if (inMST[u] == true && inMST[v] == true)// if edge u-v is already been used
		return false;
	return true;
}

void primMST(int cost[][V]){

	cout << "" << endl;
	graph_convert();
	//
	vector<bool> inMST(V, false);

	// Include first vertex in MST 
	inMST[0] = true;

	// Keep adding edges while number of included 
	// edges does not become V-1. 
	int edge_count = 0, mincost = 0;
	//The MST cannot exceed the number of vertices 
	while (edge_count < V - 1) {

		// Find valid edge with the smallest weight    
		int min = INT_MAX, 
			//initialized to a value outside of what's possible
			a = -1, b = -1;

		for (int i = 0; i < V; i++) {
			for (int j = 0; j < V; j++) {
				// if the weight at the node is less than the current minimum...
				if (cost[i][j] < min) {
					//check to see if the edge between is valid.
					if (isValidEdge(i, j, inMST)) {
						//if it is update the minimum.
						min = cost[i][j];
						a = i;
						b = j;
					}
				}
			}
		}
		//if a and b are valid graph coordinates.
		if (a != -1 && b != -1) {
			printf("Edge %d:(%d, %d) cost: %d \n",
				edge_count++, a, b, min);
			mincost = mincost + min;
			inMST[b] = inMST[a] = true;
		}
	}
	printf("\n Minimum cost= %d \n", mincost);
}


int main()
{
	/* Let us create the example graph discussed above */


	dijkstra(graph, 0);
	
	primMST(graph);
	return 0;
}