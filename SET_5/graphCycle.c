#include <stdio.h>

#define N 4

int graph[N][N] = {
    {0, 1, 1, 0},
    {0, 0, 1, 0},
    {1, 0, 0, 1},
    {0, 0, 0, 1}
};

int visited[N];
int path[N];
int pathIndex = 0;

int minLength = N + 1;
int maxLength = 0;

int minCycle[N + 1];
int maxCycle[N + 1];

void saveCycle(int length)
{
    if (length < minLength)
    {
        minLength = length;

        for (int i = 0; i < length; i++)
            minCycle[i] = path[i];

        minCycle[length] = path[0];
    }

    if (length > maxLength)
    {
        maxLength = length;

        for (int i = 0; i < length; i++)
            maxCycle[i] = path[i];

        maxCycle[length] = path[0];
    }
}

void DFS(int start, int current)
{
    for (int next = 0; next < N; next++)
    {
        if (graph[current][next])
        {
            /* Cycle found */
            if (next == start)
            {
                saveCycle(pathIndex);
            }

            /* Visit unvisited vertex */
            else if (!visited[next])
            {
                visited[next] = 1;
                path[pathIndex++] = next;

                DFS(start, next);

                pathIndex--;
                visited[next] = 0;
            }
        }
    }
}

void findCycles()
{
    for (int start = 0; start < N; start++)
    {
        for (int i = 0; i < N; i++)
            visited[i] = 0;

        pathIndex = 1;
        path[0] = start;
        visited[start] = 1;

        DFS(start, start);
    }
}

void printCycle(int cycle[], int length)
{
    for (int i = 0; i <= length; i++)
    {
        printf("%d", cycle[i]);

        if (i < length)
            printf(" -> ");
    }

    printf("\n");
}

int main()
{
    findCycles();

    if (maxLength == 0)
    {
        printf("No cycle found.\n");
        return 0;
    }

    printf("Smallest Cycle: ");
    printCycle(minCycle, minLength);
    printf("Length = %d\n\n", minLength);

    printf("Largest Cycle: ");
    printCycle(maxCycle, maxLength);
    printf("Length = %d\n", maxLength);

    return 0;
}