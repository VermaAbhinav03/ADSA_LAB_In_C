#include <stdio.h>

typedef struct
{
    char id;
    int deadline;
    int profit;
} Job;

void jobSequencing(Job jobs[], int n)
{
    // Sort by decreasing profit
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (jobs[i].profit < jobs[j].profit)
            {
                Job temp = jobs[i];
                jobs[i] = jobs[j];
                jobs[j] = temp;
            }
        }
    }

    int slot[20] = {0};
    char result[20];

    for (int i = 0; i < n; i++)
    {
        // Find latest free slot
        for (int j = jobs[i].deadline; j >= 1; j--)
        {
            if (slot[j] == 0)
            {
                slot[j] = 1;
                result[j] = jobs[i].id;
                break;
            }
        }
    }

    printf("Job sequence: ");

    for (int i = 1; i <= n; i++)
    {
        if (slot[i])
            printf("%c ", result[i]);
    }

    printf("\n");
}

int main()
{
    Job jobs[] =
    {
        {'A', 2, 100},
        {'B', 1, 19},
        {'C', 2, 27},
        {'D', 1, 25},
        {'E', 3, 15}
    };

    int n = 5;

    jobSequencing(jobs, n);

    return 0;
}