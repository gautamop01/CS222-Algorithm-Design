#include<stdio.h>
#include<stdlib.h>

class graph
{
	int adjMatrix[100][100];/*DO NOT MODIFY THE ORIGINAL ADJACENCY MATRIX AND YOU SHOULD CREATE A COPY INSIDE YOUR FUNCTIONS TO WORK WITH*/
	int vCount;
	public:
	graph(int vertexCount)
	{
		vCount=vertexCount;
	}

	void readAdjMatrix(FILE*fp)//reads adjacency matrix from the file
	{	
		for(int i=0;i<vCount;i++)
			for(int j=0;j<vCount;j++)
				fscanf(fp,"%d",&adjMatrix[i][j]);

	}


	void findOutDegree(int u)
	{
		int outDegree;
		/*Write your code here*/
	//	printf("\n The out degree of vertex %d is %d\n",u,outDegree);
	}


	void checkPath(int vertexList[],int pathLength)
	{
		/*Write your code to print the missing edges*/				
	}
		
	void expandVertex(int u)
	{
		int adjTemp[100][100];/*Modify this copy of the adjacency matrix and keep the original the same*/
		for(int i=0;i<vCount;i++)
			for(int j=0;j<vCount;j++)
				adjTemp[i][j]=adjMatrix[i][j];
		/*Prints the modified adjacency matrix of the graph obtained by expanding the vertex u*/	
	}
	
	void replaceEdge(int u,int v)
	{
		int adjTemp[100][100];/*Modify this copy of the adjacency matrix and keep the original the same*/
		for(int i=0;i<vCount;i++)
			for(int j=0;j<vCount;j++)
				adjTemp[i][j]=adjMatrix[i][j];

		/*Prints the modified adjacency matrix of the graph obtained by replacing the edge u->v*/
	}

	void printAdjMatrix()//prints adjacency matrix
	{
	}
}*myGraph;


int main(int argc, char**argv)
{
	int vertexCount;
	int source;
	int l;
	int vList[10];
	FILE*fp=fopen(argv[1],"r");
	fscanf(fp,"%d",&vertexCount);
	myGraph=new graph(vertexCount);//initialize vertex count from the file
	
	myGraph->readAdjMatrix(fp);
	fclose(fp);
	myGraph->findOutDegree(4);
	printf("\n Enter the length of the path:");
	scanf("%d",&l);
	for(int i=0;i<l;i++)
		scanf("%d",&vList[i]);
	myGraph->checkPath(vList,l);
	myGraph->expandVertex(3);
	myGraph->replaceEdge(1,3);
}
