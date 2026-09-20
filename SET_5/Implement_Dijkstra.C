#include <stdio.h>
#include <limits.h>

#define V 5

// Find the unvisited vertex with minimum distance
int findMinDistance(int dist[], int visited[])
{
    int min = INT_MAX;
    int minIndex = -1;

    for (int i = 0; i < V; i++)
    {
        if (visited[i] == 0 && dist[i] < min)
        {
            min = dist[i];
            minIndex = i;
        }
    }

    return minIndex;
}

// Dijkstra's algorithm
void dijAlgo(int graph[V][V], int source)
{
    int dist[V];
    int visited[V];

    // Initialize arrays
    for (int i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }

    // Distance from source to itself is 0
    dist[source] = 0;

    // Find shortest paths
    for (int count = 0; count < V - 1; count++)
    {
        // Pick minimum-distance unvisited vertex
        int u = findMinDistance(dist, visited);

        // Mark it as visited
        visited[u] = 1;

        // Update distances of neighbors
        for (int v = 0; v < V; v++)
        {
            if (visited[v] == 0 &&    //Only update vertices that haven't been finalized yet.
                graph[u][v] != 0 &&   //There must be an edge from u to v
                dist[u] != INT_MAX && //We must actually be able to reach u
                dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printf("Vertex\tShortest Distance\n");

    for (int i = 0; i < V; i++)
    {
        printf("%d\t%d\n", i, dist[i]);
    }
}

int main()
{
    int graph[V][V] =
    {
        {0, 4, 1, 0, 0},
        {4, 0, 0, 2, 0},
        {1, 0, 0, 3, 5},
        {0, 2, 3, 0, 1},
        {0, 0, 5, 1, 0}
    };

    int source = 0;

    dijAlgo(graph, source);

    return 0;
}