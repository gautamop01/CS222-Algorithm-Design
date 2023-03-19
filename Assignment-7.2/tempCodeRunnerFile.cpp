    int countEdge()
    {
        int count = 0;
        for (int i = 1; i <= vCount; i++)
        {
            for (int j = 1; j <= vCount; j++)
            {
                if (adjMatrix[i][j] != 0)
                {
                    count++;
                }
            }
        }
        edgeCount = count;
        return edgeCount;
    }
    void runDijkstra(int startVertex) // Run Dijkstra's Algorithm with the given startVertex and load the associated data structures with necessary information
    {
        superSource = startVertex;
        bool *visited = new bool[vCount];
        for (int i = 1; i <= vCount; i++)
        {
            distListDijkstra[i] = INT_MAX;
            visited[i] = false;
            predListDijkstra[i] = -1;
        }
        distListDijkstra[startVertex] = 0;

        for (int count = 1; count <= vCount - 1; count++)
        {
            int min = INT_MAX, u;
            for (int i = 1; i <= vCount; i++)
            {
                if (!visited[i] && distListDijkstra[i] <= min)
                {
                    min = distListDijkstra[i], u = i;
                }
            }

            visited[u] = true;

            for (neighborList *ptr = adjList[u]; ptr != NULL; ptr = ptr->next)
            {
                int v = ptr->neighborIndex;
                int weight = ptr->weight;
                if (!visited[v] && distListDijkstra[u] + weight < distListDijkstra[v])
                {
                    distListDijkstra[v] = distListDijkstra[u] + weight;
                    predListDijkstra[v] = u;
                }
            }
        }
    }
    void testDijkstra()
    {
        printf("\nSortest Distence from super Source :: %d ", superSource);
        printf("\n");
        printf("Vertex \t\t Distance from Source\n");
        for (int i = 1; i <= vCount; i++)
        {
            printf("%d \t\t\t\t %03d\n", i, distListDijkstra[i]);
        }
        printf("\n");
    }

    void printDijkstraPathTo(int targetVertex) // superSource->......->tergetVertex     lengthOfPath/
    {
        if (distListDijkstra[targetVertex] == INT_MAX)
        {
            printf("No path from %d to %d\n", superSource, targetVertex);
        }
        else
        {
            int *path = new int[vCount];
            int pathLen = 1;
            int u = targetVertex;
            while (u != superSource)
            {
                path[pathLen++] = u;
                u = predListDijkstra[u];
            }
            path[pathLen++] = superSource;
            printf("\n%d", path[pathLen - 1]);
            for (int i = pathLen - 2; i > 0; i--)
            {
                printf("->%d", path[i]);
            }
            printf("\t\tLength Of Path(Dijkstra's Algorithm) = %d\n", distListDijkstra[targetVertex]);
            delete[] path;
        }
    }
    void runFW() // Run Floyd-Warshall Algorithm and fill in the associated data structures with necessary information
    {
        for (int i = 1; i <= vCount; i++)
        {
            for (int j = 1; j <= vCount; j++)
            {
                distListFW[i][j] = adjMatrix[i][j];
                if (adjMatrix[i][j] != INT_MAX)
                {
                    if (distListFW[i][j] == 0 && i != j)
                    {
                        distListFW[i][j] = INT_MAX;
                    }
                    predListFW[i][j] = j;
                }
                else
                {
                    predListFW[i][j] = -1;
                }
            }
        }
        for (int k = 1; k <= vCount; k++)
        {
            for (int i = 1; i <= vCount; i++)
            {
                for (int j = 1; j <= vCount; j++)
                {
                    if (distListFW[i][k] != INT_MAX && distListFW[k][j] != INT_MAX && distListFW[i][k] + distListFW[k][j] < distListFW[i][j])
                    {
                        distListFW[i][j] = distListFW[i][k] + distListFW[k][j];
                        predListFW[i][j] = predListFW[i][k];
                    }
                }
            }
        }
    }
    void printFWPathBetween(int sourceVertex, int targetVertex) // sourceVertex->......->targetVertex     lengthOfPath/
    {
        if (distListFW[sourceVertex][targetVertex] == INT_MAX)
        {
            printf("No path exists between vertex %d and vertex %d.\n", sourceVertex, targetVertex);
            return;
        }
        int u = sourceVertex;
        printf("%d", u);
        while (u != targetVertex)
        {
            u = predListFW[u][targetVertex];
            printf("->%d", u);
        }

        printf("\t\tLength Of Path(floyd Warshall Algorithm)= %d\n", distListFW[sourceVertex][targetVertex]);
    }
    void testFW()
    {
        printf("\nThe following matrix shows the shortest distance between every pair of vertices: \n");
        printf("\n");
        for (int i = 1; i <= vCount; i++)
        {
            for (int j = 1; j <= vCount; j++)
            {
                if (distListFW[i][j] == INT_MAX)
                    printf("%7s", "INF");
                else
                    printf("%03d ", distListFW[i][j]);
            }
            printf("\n");
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

    printf("\nThere are %d edges in the graph\n", myGraph->countEdge());
    printf("\n");
    myGraph->loadAdjList();
    myGraph->printAdjMatrix();
    myGraph->printAdjList();

    printf("\nEnter the super source vertex for Dijkstra's Algorithm: ");
    scanf("%d", &source);
    myGraph->runDijkstra(source);
    myGraph->printDijkstraPathTo(3);
    myGraph->testDijkstra();
    myGraph->runFW();
    myGraph->printFWPathBetween(source, 3);
    myGraph->testFW();
}