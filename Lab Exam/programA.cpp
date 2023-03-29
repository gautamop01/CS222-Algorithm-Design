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


	void findInDegree(int u)
	{
		int inDegree;
		/*Write your code here*/
	//	printf("\n The indegree of vertex %d is %d\n",u,inDegree);
	}


	void findPathWeight(int vertexList[],int pathLength)
	{
		int wt;
		/*Write your code here*/				
	}
		
	void deleteVertex(int u)
	{
		int adjTemp[100][100];/*Modify this copy of the adjacency matrix and keep the original the same*/
		for(int i=0;i<vCount;i++)
			for(int j=0;j<vCount;j++)
				adjTemp[i][j]=adjMatrix[i][j];
		/*Prints the modified adjacency matrix of the graph obtained by deleting the vertex u*/	
	}
	
	void contractEdge(int u,int v)
	{
		int adjTemp[100][100];/*Modify this copy of the adjacency matrix and keep the original the same*/
		for(int i=0;i<vCount;i++)
			for(int j=0;j<vCount;j++)
				adjTemp[i][j]=adjMatrix[i][j];

		/*Prints the modified adjacency matrix of the graph obtained by contracting edge u->v*/
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
	myGraph->findInDegree(4);
	printf("\n Enter the length of the path:");
	scanf("%d",&l);
	for(int i=0;i<l;i++)
		scanf("%d",&vList[i]);
	myGraph->findPathWeight(vList,l);
	myGraph->deleteVertex(3);
	myGraph->contractEdge(1,3);
}
