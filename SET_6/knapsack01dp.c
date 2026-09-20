#include <stdio.h>

#define N 4
#define W 5

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int main()
{
    int weight[N] = {2, 1, 3, 2};
    int profit[N] = {12, 10, 20, 15};

    int dp[N + 1][W + 1];

    // Initialize
    for (int i = 0; i <= N; i++)
    {
        for (int w = 0; w <= W; w++)
        {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (weight[i - 1] <= w)
                dp[i][w] = max(
                    profit[i - 1] +
                    dp[i - 1][w - weight[i - 1]],
                    dp[i - 1][w]
                );
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    printf("Maximum profit = %d\n", dp[N][W]);

    return 0;
}