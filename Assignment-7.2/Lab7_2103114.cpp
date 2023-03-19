/*
Name - Gautam Kumar Mahar
Roll Number - 2103114
Branch - CSE
Date - 17 March 2023
Assignment 7.2
*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <climits>
using namespace std;
struct neighborList // structure of  in the adjacency list
{
	int neighborIndex;		   // index of the neighbor
	int weight;				   // weight of the edge
	struct neighborList *next; // next pointer
};

class graph
{
	int vCount;				// vertex count
	int **adjMatrix;		// adjacency matrix
	neighborList **adjList; // adjacency list
	int edgeCount;			// edge count
	int superSource;		// source vertex for Dijkstra's Algorithm
	int *predListDijkstra;	// predecessor list from Dijkstra's Algorithm
	int **predListFW;		// predecessor list from Floyd-Warshall Algorithm

	int *distListDijkstra; // distance details from Dijkstra's Algorithm
	int **distListFW;	   // distance details from FW Algorithm

public:
	graph(int vertexCount)
	{
		vCount = vertexCount;
		edgeCount = 0;
		allocateMem();
	}

	void allocateMem() // allocates memory for the necessary data structures
	{
		adjMatrix = new int *[vCount];
		adjList = new neighborList *[vCount];
		for (int i = 1; i <= vCount; i++)
		{
			adjMatrix[i] = new int[vCount];
			adjList[i] = NULL;
		}

		predListDijkstra = new int[vCount];
		distListDijkstra = new int[vCount];
		predListFW = new int *[vCount];
		distListFW = new int *[vCount];
		for (int i = 1; i <= vCount; i++)
		{
			predListFW[i] = new int[vCount];
			distListFW[i] = new int[vCount];
		}
	}
	void readAdjMatrix(FILE *fp) // reads adjacency matrix from the file
	{
		// loop through each row and column of the adjacency matrix
		for (int i = 1; i <= vCount; i++)
			for (int j = 1; j <= vCount; j++)
				fscanf(fp, "%d", &adjMatrix[i][j]); // read the integer value at the current row and column and store it in the adjacency matrix
	}

	void printAdjMatrix() // prints adjacency matrix
	{
		// loop through each row of the adjacency matrix
		for (int i = 1; i <= vCount; i++)
		{
			// loop through each column of the current row
			for (int j = 1; j <= vCount; j++)
			{
				printf("%d ", adjMatrix[i][j]); // print the integer value at the current row and column
				printf(" ");					// add a space for formatting purposes
			}
			printf("\n"); // move to a new line after each row is printed
		}
	}

	void loadAdjList() // set up the adjacency list
	{
		// create a neighborList node for each vertex in the graph
		for (int k = 1; k <= vCount; k++)
		{
			neighborList *trash;	  // declare a new neighborList node
			trash = new neighborList; // allocate memory for the node
			trash->neighborIndex = k; // set the node's neighborIndex value to the current vertex
			trash->weight = 0;		  // set the node's weight value to 0
			trash->next = NULL;		  // set the node's next pointer to NULL
			adjList[k] = trash;		  // assign the node to the corresponding position in the adjList array
		}
		// loop through each row and column of the adjacency matrix
		for (int i = 1; i <= vCount; i++)
		{
			for (int j = 1; j <= vCount; j++)
			{
				if (adjMatrix[i][j] != 0) // if there is an edge between the current vertices
				{
					neighborList *current;			   // declare a new neighborList node
					current = new neighborList;		   // allocate memory for the node
					current->next = NULL;			   // set the node's next pointer to NULL
					current->neighborIndex = j;		   // set the node's neighborIndex value to the vertex connected by the edge
					current->weight = adjMatrix[i][j]; // set the node's weight value to the weight of the edge
					neighborList *it = adjList[i];	   // create a pointer to the current vertex's neighborList
					while (it->next != NULL)
					{ // traverse the neighborList to find the last node
						it = it->next;
					}
					it->next = current; // add the new node to the end of the neighborList
				}
			}
		}
	}

	void printAdjList()
	{
		// loop through each vertex in the graph
		for (int i = 1; i <= vCount; i++)
		{
			printf("%d ", i);					// print the vertex index
			neighborList *current = adjList[i]; // create a pointer to the current vertex's neighborList
			// loop through each neighbor of the current vertex
			while (current != NULL)
			{
				printf("-> (%d,%d)", current->neighborIndex, current->weight); // print the neighbor's index and weight
				current = current->next;									   // move to the next neighbor in the list
			}
			printf("-> NULL\n"); // print NULL to indicate the end of the neighborList for the current vertex
		}
	}

	int countEdge()
	{
		int count = 0; // initialize a counter for the number of edges in the graph
		// loop through each row and column of the adjacency matrix
		for (int i = 1; i <= vCount; i++)
		{
			for (int j = 1; j <= vCount; j++)
			{
				if (adjMatrix[i][j] != 0) // if there is an edge between the current vertices
				{
					edgeCount++; // increment the edge count
				}
			}
		}
		return edgeCount; // return the total number of edges in the graph
	}
	void runDijkstra(int VERTEX_START) // Run Dijkstra's Algorithm with the given VERTEX_START and load the associated data structures with necessary information
	{
		superSource = VERTEX_START;		  // set the superSource to the given VERTEX_START
		bool *visited = new bool[vCount]; // create a boolean array to keep track of which vertices have been visited
		for (int i = 1; i <= vCount; i++)
		{
			distListDijkstra[i] = INT_MAX; // initialize the distance list to a very large value
			visited[i] = false;			   // mark all vertices as unvisited
			predListDijkstra[i] = -1;	   // initialize the predecessor list to -1 for all vertices
		}
		distListDijkstra[VERTEX_START] = 0; // set the distance to the starting vertex to 0

		for (int count = 1; count <= vCount - 1; count++) // repeat vCount - 1 times
		{
			int min = INT_MAX, u;
			for (int i = 1; i <= vCount; i++) // find the unvisited vertex with the minimum distance
			{
				if (!visited[i] && distListDijkstra[i] <= min)
				{
					min = distListDijkstra[i], u = i;
				}
			}

			visited[u] = true; // mark the selected vertex as visited

			for (neighborList *ptr = adjList[u]; ptr != NULL; ptr = ptr->next) // update the distances of adjacent vertices
			{
				int v = ptr->neighborIndex;											   // get the index of the adjacent vertex
				int weight = ptr->weight;											   // get the weight of the edge connecting the two vertices
				if (!visited[v] && distListDijkstra[u] + weight < distListDijkstra[v]) // if the new distance is smaller than the previous distance, update the distance and predecessor lists
				{
					distListDijkstra[v] = distListDijkstra[u] + weight;
					predListDijkstra[v] = u;
				}
			}
		}
	}

	void testDijkstra()
	{
		printf("\nThe Shortest Distance from super Source is --> %d ", superSource); // print the source vertex
		printf("\n");
		printf("\t\tThe Vertex \t\t\t\t Distance from Source\n");
		for (int i = 1; i <= vCount; i++) // print the distance of each vertex from the source
		{
			printf("\t\t\t%d \t\t\t\t\t\t %03d\n", i, distListDijkstra[i]);
		}
		printf("\n");
	}

	void printDijkstraPathTo(int TARGET_VERTEX)
	{
		// Check if there is a path from the superSource to the target vertex
		if (distListDijkstra[TARGET_VERTEX] == INT_MAX)
		{
			printf("No path from %d to %d\n", superSource, TARGET_VERTEX);
		}
		else
		{
			// Create an array to store the path vertices
			int *path = new int[vCount];
			int pathLen = 1;
			// Starting from the target vertex, follow the predecessor list to get the shortest path
			int u = TARGET_VERTEX;
			while (u != superSource)
			{
				path[pathLen++] = u;
				u = predListDijkstra[u];
			}
			// Add the superSource to the path
			path[pathLen++] = superSource;
			// Print the vertices of the path in reverse order
			printf("\n%d", path[pathLen - 1]);
			for (int i = pathLen - 2; i > 0; i--)
			{
				printf("->%d", path[i]);
			}
			// Print the length of the path
			printf("\t\t Path Length for Dijkstra's Algorithm = %d\n", distListDijkstra[TARGET_VERTEX]);
			// Free the memory allocated for the path array
			delete[] path;
		}
	}

	void runFW()
	{
		// Initialize the distance and predecessor lists with the values from the adjacency matrix
		for (int i = 1; i <= vCount; i++)
		{
			for (int j = 1; j <= vCount; j++)
			{
				distListFW[i][j] = adjMatrix[i][j];
				if (adjMatrix[i][j] != INT_MAX)
				{
					if (distListFW[i][j] == 0 && i != j)
					{
						// If there is a self-loop, set the distance to INT_MAX
						distListFW[i][j] = INT_MAX;
					}
					predListFW[i][j] = j;
				}
				else
				{
					// If there is no edge, set the predecessor to -1
					predListFW[i][j] = -1;
				}
			}
		}
		// Run the Floyd-Warshall algorithm to compute the shortest path between every pair of vertices
		for (int k = 1; k <= vCount; k++)
		{
			for (int i = 1; i <= vCount; i++)
			{
				for (int j = 1; j <= vCount; j++)
				{
					if (distListFW[i][k] != INT_MAX && distListFW[k][j] != INT_MAX && distListFW[i][k] + distListFW[k][j] < distListFW[i][j])
					{
						// If there is a shorter path through vertex k, update the distance and predecessor lists
						distListFW[i][j] = distListFW[i][k] + distListFW[k][j];
						predListFW[i][j] = predListFW[i][k];
					}
				}
			}
		}
	}

	void printFWPathBetween(int SOURCE_VERTEX, int TARGET_VERTEX) // function to print the shortest path between two vertices using Floyd-Warshall Algorithm
	{
		// if no path exists between the given source and target vertices
		if (distListFW[SOURCE_VERTEX][TARGET_VERTEX] == INT_MAX)
		{
			printf("Here, No path exists between vertex %d and vertex %d.\n", SOURCE_VERTEX, TARGET_VERTEX);
			return;
		}

		int u = SOURCE_VERTEX; // set the current vertex to the source vertex
		printf("\t\t\t%d", u); // print the source vertex

		// traverse the predListFW to get the vertices in the shortest path from source to target vertex
		while (u != TARGET_VERTEX)
		{
			u = predListFW[u][TARGET_VERTEX];
			printf("->%d", u); // print each vertex in the shortest path
		}

		printf("\t\t\t\t Path Length for floyd Warshall Algorithm = %d\n", distListFW[SOURCE_VERTEX][TARGET_VERTEX]); // print the length of the shortest path
	}

	void testFW() // function to test the Floyd-Warshall Algorithm and print the resulting distance matrix
	{
		printf("\n\nHere, this matrix shows shortest distance between every pair of vertices --> \n");
		printf("\n");
		for (int i = 1 + 1 - 1; i <= vCount; i++) // loop through all vertices
		{
			for (int j = 1; j <= vCount; j++)
			{
				// if there is no path between vertex i and vertex j
				if (distListFW[i][j] == INT_MAX)
					printf("%7s", "INF"); // print INF to represent infinity
				else
					printf("%03d ", distListFW[i][j]); // print the distance between vertex i and vertex j
			}
			printf("\n"); // move to the next row
		}
	}

} *myGraph;
int main(int argc, char **argv)
{
	int vertexCount;
	int source;
	FILE *fp = fopen(argv[1], "r");
	fscanf(fp, "%d", &vertexCount);
	myGraph = new graph(vertexCount); // initialize vertex count from the file

	myGraph->readAdjMatrix(fp);
	fclose(fp);
	printf("There are %d edges in the graph :\n", myGraph->countEdge());

	myGraph->loadAdjList();
	myGraph->printAdjMatrix();
	printf("Here is the adjacency list representation is :\n");
	myGraph->printAdjList();

	printf("\nPlease Enter the super source vertex for Dijkstra's Algorithm--> ");
	scanf("%d", &source);
	myGraph->runDijkstra(source);
	myGraph->printDijkstraPathTo(3);
	myGraph->testDijkstra();
	myGraph->runFW();
	myGraph->printFWPathBetween(source, 3);
	myGraph->testFW();
}
