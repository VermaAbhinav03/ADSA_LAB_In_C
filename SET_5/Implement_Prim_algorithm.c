#include <stdio.h>

#define V 4

int main()
{
    int graph[V][V] = {
        {0, 2, 6, 3},
        {2, 0, 0, 5},
        {6, 0, 0, 1},
        {3, 5, 1, 0}
    };

    int visited[V] = {0};

    int edgeCount = 0;
    int totalCost = 0;

    printf("Minimum Spanning Tree Edges:\n");

    // Start from vertex 0
    visited[0] = 1;

    while (edgeCount < V - 1)
    {
        int min = 9999;
        int x = -1;
        int y = -1;

        // Find the minimum edge
        // connecting visited vertex to unvisited vertex
        for (int i = 0; i < V; i++)
        {
            if (visited[i] == 1) //Only consider vertices that are already inside the MST
            {
                for (int j = 0; j < V; j++)
                {
                    if (visited[j] == 0 && //Vertex j must NOT already be in the MST.
                        graph[i][j] != 0)  //means there is edge between i and j
                    {
                        if (graph[i][j] < min)
                        {
                            min = graph[i][j];
                            x = i;
                            y = j;
                        }
                    }
                }
            }
        }

        // Add selected edge to MST
        printf("%d - %d : %d\n", x, y, min);

        totalCost += min;

        visited[y] = 1;

        edgeCount++;
    }

    printf("Total cost of MST = %d\n", totalCost);

    return 0;
}