/*
Name - Gautam Kumar Mahar 
Roll Number - 2103114
Branch - CSE
Date - 06 March 2023
Assignment 7.1
*/
#include <stdio.h>
#include <stdlib.h>

struct neighborList // structure of a node in the adjacency list
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
		for (int i = 0; i < vCount; i++)
		{
			adjMatrix[i] = new int[vCount];
			adjList[i] = NULL;
		}

		predListDijkstra = new int[vCount];
		distListDijkstra = new int[vCount];
		predListFW = new int *[vCount];
		distListFW = new int *[vCount];
		for (int i = 0; i < vCount; i++)
		{
			predListFW[i] = new int[vCount];
			distListFW[i] = new int[vCount];
		}
	}
	void readAdjMatrix(FILE *fp) // reads adjacency matrix from the file
	{
		for (int i = 0; i < vCount; i++)
			for (int j = 0; j < vCount; j++)
				fscanf(fp, "%d", &adjMatrix[i][j]);
	}

	void printAdjMatrix() // prints adjacency matrix
	{
		for (int i = 0; i < vCount; i++)
		{
			for (int j = 0; j < vCount; j++)
			{
				printf("%d ", adjMatrix[i][j]);
				printf(" ");
			}
			printf("\n");
		}
	}

	void loadAdjList() // set up the adjacency list
	{   
        
        for (int k = 0; k < vCount; k++)
        {
            neighborList* trash;
            trash = new neighborList;
            trash->neighborIndex = k+1;
            trash->weight = 0;
            trash->next = NULL;
            adjList[k] = trash;
            
        }
        for (int i = 0; i < vCount; i++)
        {
            for (int j = 0; j < vCount; j++)
            {
                if (adjMatrix[i][j] != 0)
                {
                    neighborList *current;
                    current = new neighborList;
                    current->next = NULL;
                    current->neighborIndex = j + 1;
                    current->weight = adjMatrix[i][j];
                    neighborList* it = adjList[i];
                    while(it->next != NULL){
                        it = it->next;
                    }
                    it->next = current;
                    
                }
            }
        }
    }

	void printAdjList()
	{
    for(int i=0; i<vCount; i++)
    {
        printf("%d ", i+1);
        neighborList* current = adjList[i];
        while(current != NULL)
        {
            printf("-> (%d,%d)", current->neighborIndex, current->weight);
            current = current->next;
        }
        printf("-> NULL\n");
    }
}

	int countEdge() // count the number of edges in the graph
	{
		int count = 0;
		for (int i = 0; i < vCount; i++)
		{
			for (int j = 0; j < vCount; j++)
			{
				if (adjMatrix[i][j] != 0)
				{
					edgeCount++;
				}
			}
		}
		return edgeCount;
	}

	void runDijkstra(int startVertex)// Run Dijkstra's Algorithm with the given startVertex and load the associated data structures with necessary information
	{
		superSource=startVertex;
	}
	void runFW()//Run Floyd-Warshall Algorithm and fill in the associated data structures with necessary information
	{

	}
	void printDijkstraPathTo(int targetVertex)/*superSource->......->tergetVertex     lengthOfPath*/
	{

	}
	void printFWPathBetween(int sourceVertex, int targetVertex)/*sourceVertex->......->targetVertex     lengthOfPath*/
	{

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
	printf("There are %d edges in the graph :\n",myGraph->countEdge());

	myGraph->printAdjMatrix();
        myGraph->loadAdjList();
        printf("Here is the adjacency list representation is :\n");
        myGraph->printAdjList();	


		// printf("\n Enter the super source vertex for Dijkstra's Algorithm:");
		// 	scanf("%d",&source);
		// runDijkstra(source);
		// runFW();
		// testDijkstra();s
		// testFW();
	
}
