#include <stdio.h>
#include <stdlib.h>

#define N 16

int goal[N] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};

int heuristic(int a[])
{
    int h = 0;

    for (int i = 0; i < N; i++)
    {
        if (a[i] != 0)
        {
            int g = a[i] - 1;
            h += abs(i / 4 - g / 4) +
                 abs(i % 4 - g % 4);
        }
    }

    return h;
}

int isGoal(int a[])
{
    for (int i = 0; i < N; i++)
        if (a[i] != goal[i])
            return 0;

    return 1;
}

void print(int a[])
{
    for (int i = 0; i < N; i++)
    {
        if (a[i] == 0)
            printf("_ ");
        else
            printf("%d ", a[i]);

        if (i % 4 == 3)
            printf("\n");
    }
    printf("\n");
}

void solve(int a[])
{
    int blank = 14;

    printf("Initial State:\n");
    print(a);

    // Move blank to the right
    if (blank % 4 < 3)
    {
        int temp = a[blank];
        a[blank] = a[blank + 1];
        a[blank + 1] = temp;
    }

    printf("After one Branch and Bound move:\n");
    print(a);

    printf("Cost = g + h = 1 + %d\n", heuristic(a));

    if (isGoal(a))
        printf("Goal Reached!\n");
}

int main()
{
    int puzzle[N] =
    {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 0,
        13, 14, 15, 12
    };

    solve(puzzle);

    return 0;
}