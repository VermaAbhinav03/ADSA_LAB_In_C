#include <stdio.h>

#define V 5
#define INF 99999

void bellmanFord(int graph[V][V], int src)
{
    int dist[V];

    for (int i = 0; i < V; i++)
        dist[i] = INF;

    dist[src] = 0;

    // Relax all edges V-1 times
    for (int k = 1; k <= V - 1; k++)
    {
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                if (graph[i][j] != 0 &&
                    dist[i] != INF &&
                    dist[i] + graph[i][j] < dist[j])
                {
                    dist[j] = dist[i] + graph[i][j];
                }
            }
        }
    }

    // Check negative cycle
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (graph[i][j] != 0 &&
                dist[i] != INF &&
                dist[i] + graph[i][j] < dist[j])
            {
                printf("Negative weight cycle exists!\n");
                return;
            }
        }
    }

    printf("Shortest distances from vertex %d:\n", src);

    for (int i = 0; i < V; i++)
        printf("%d -> %d = %d\n", src, i, dist[i]);
}

int main()
{
    int graph[V][V] =
    {
        {0, 10, 5, 0, 0},
        {0, 0, 0, -2, 0},
        {0, 0, 0, 2, 0},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0}
    };

    bellmanFord(graph, 0);

    return 0;
}