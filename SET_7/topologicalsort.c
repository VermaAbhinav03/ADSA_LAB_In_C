#include <stdio.h>

#define V 5

int graph[V][V] =
{
    {0,1,1,0,0},
    {0,0,1,1,0},
    {0,0,0,1,0},
    {0,0,0,0,1},
    {0,0,0,0,0}
};

int visited[V];
int stack[V], top = -1;

void DFS(int v)
{
    visited[v] = 1;

    for (int i = 0; i < V; i++)
        if (graph[v][i] && !visited[i])
            DFS(i);

    stack[++top] = v;
}

int main()
{
    for (int i = 0; i < V; i++)
        if (!visited[i])
            DFS(i);

    printf("Topological Order: ");

    while (top >= 0)
        printf("%d ", stack[top--]);

    return 0;
}