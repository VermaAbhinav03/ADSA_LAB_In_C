#include <stdio.h>

#define N 5
#define INF 9999

int graph[N][N] =
{
    {0,10,15,20,25},
    {10,0,35,25,30},
    {15,35,0,30,20},
    {20,25,30,0,10},
    {25,30,20,10,0}
};

int visited[N];
int minCost = INF;

void TSP(int city, int count, int cost)
{
    if (count == N)
    {
        if (graph[city][0] != 0)
        {
            int total = cost + graph[city][0];

            if (total < minCost)
                minCost = total;
        }

        return;
    }

    for (int i = 0; i < N; i++)
    {
        if (!visited[i] && graph[city][i] != 0)
        {
            visited[i] = 1;

            TSP(i, count + 1,
                cost + graph[city][i]);

            visited[i] = 0;
        }
    }
}

int main()
{
    visited[0] = 1;

    TSP(0, 1, 0);

    printf("Minimum TSP cost = %d\n", minCost);

    return 0;
}