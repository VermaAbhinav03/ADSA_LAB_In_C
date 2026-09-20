#include <stdio.h>

#define N 5

int graph[N][N] = {
    {0,1,1,0,0},
    {1,0,0,1,0},
    {1,0,0,1,0},
    {0,1,1,0,1},
    {0,0,0,1,0}
};

int color[N];

int bipartite()
{
    int q[N], front=0, rear=0;
    int i, v;

    for(i=0;i<N;i++)
        color[i] = -1;

    color[0] = 0;
    q[rear++] = 0;

    while(front < rear) {
        v = q[front++];

        for(i=0;i<N;i++) {
            if(graph[v][i]) {
                if(color[i] == -1) {
                    color[i] = 1 - color[v];
                    q[rear++] = i;
                }
                else if(color[i] == color[v])
                    return 0;
            }
        }
    }

    return 1;
}

int main()
{
    if(bipartite())
        printf("Graph is Bipartite\n");
    else
        printf("Graph is not Bipartite\n");

    return 0;
}