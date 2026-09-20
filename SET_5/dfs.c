#include <stdio.h>

#define N 4

int graph[N][N] = {
    {0, 1, 1, 0},
    {0, 0, 1, 0},
    {1, 0, 0, 1},
    {0, 0, 0, 1}
};

int color[N];       // 0 = White, 1 = Gray, 2 = Black
int discover[N];
int finish[N];
int time = 0;

void DFSVisit(int u)
{
    color[u] = 1;              // Gray
    discover[u] = ++time;

    for (int v = 0; v < N; v++)
    {
        if (graph[u][v] == 1)
        {
            // Tree Edge
            if (color[v] == 0)
            {
                printf("%d -> %d : Tree Edge\n", u, v);
                DFSVisit(v);
            }

            // Back Edge
            else if (color[v] == 1)
            {
                printf("%d -> %d : Back Edge\n", u, v);
            }

            // Forward or Cross Edge
            else
            {
                if (discover[u] < discover[v])
                    printf("%d -> %d : Forward Edge\n", u, v);
                else
                    printf("%d -> %d : Cross Edge\n", u, v);
            }
        }
    }

    color[u] = 2;              // Black
    finish[u] = ++time;
}

void DFS()
{
    for (int i = 0; i < N; i++)
        color[i] = 0;

    for (int i = 0; i < N; i++)
    {
        if (color[i] == 0)
            DFSVisit(i);
    }
}

int main()
{
    printf("DFS Edge Classification:\n\n");

    DFS();

    printf("\nDiscovery and Finish Times:\n");

    for (int i = 0; i < N; i++)
    {
        printf("Vertex %d: d = %d, f = %d\n",
               i, discover[i], finish[i]);
    }

    return 0;
}