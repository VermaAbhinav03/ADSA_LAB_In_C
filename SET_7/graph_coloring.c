#include <stdio.h>

#define V 5
#define M 3

int graph[V][V] =
{
    {0,1,1,1,0},
    {1,0,1,0,1},
    {1,1,0,1,1},
    {1,0,1,0,1},
    {0,1,1,1,0}
};

int color[V];

int isSafe(int v, int c)
{
    for (int i = 0; i < V; i++)
        if (graph[v][i] && color[i] == c)
            return 0;

    return 1;
}

int solve(int v)
{
    if (v == V)
        return 1;

    for (int c = 1; c <= M; c++)
    {
        if (isSafe(v, c))
        {
            color[v] = c;

            if (solve(v + 1))
                return 1;

            color[v] = 0;       // Backtrack
        }
    }

    return 0;
}

int main()
{
    if (solve(0))
    {
        printf("Coloring:\n");

        for (int i = 0; i < V; i++)
            printf("Vertex %d -> Color %d\n", i, color[i]);
    }
    else
        printf("No solution\n");

    return 0;
}