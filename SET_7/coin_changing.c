#include <stdio.h>

void coinChange(int coins[], int n, int amount)
{
    int count = 0;

    printf("Coins used: ");

    for (int i = n - 1; i >= 0; i--)
    {
        while (amount >= coins[i])
        {
            amount -= coins[i];
            printf("%d ", coins[i]);
            count++;
        }
    }

    printf("\nNumber of coins = %d\n", count);
}

int main()
{
    int coins[] = {1, 5, 10, 25};
    int n = 4;
    int amount = 63;

    coinChange(coins, n, amount);

    return 0;
}