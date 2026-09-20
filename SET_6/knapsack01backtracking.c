#include <stdio.h>

#define N 4
#define W 5

int weight[N] = {2, 1, 3, 2};
int profit[N] = {12, 10, 20, 15};

int maxProfit = 0;

void knapsack(int i, int currentWeight, int currentProfit)
{
    // All items processed
    if (i == N)
    {
        if (currentProfit > maxProfit)
            maxProfit = currentProfit;

        return;
    }

    // Include current item
    if (currentWeight + weight[i] <= W)
    {
        knapsack(
            i + 1,
            currentWeight + weight[i],
            currentProfit + profit[i]
        );
    }

    // Exclude current item
    knapsack(
        i + 1,
        currentWeight,
        currentProfit
    );
}

int main()
{
    knapsack(0, 0, 0);

    printf("Maximum profit = %d\n", maxProfit);

    return 0;
}