#include <stdio.h>

void printarr(int arr[] , int SIZE){
    for(int i=0;i<SIZE;i++){
        printf("%d \t",arr[i]);
    }
    printf("\n");
}

int getMaxBit(int arr[], int n)
{
    int max = arr[0];

    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max)
            max = arr[i];
    }

    int bit = 0;

    while (max > 1)
    {
        max = max / 2;
        bit++;
    }

    return bit;
}

void radixExchangeSort(int arr[], int left, int right, int bit)
{
    if (left >= right || bit < 0)
        return;

    int i = left;
    int j = right;

    while (i <= j)
    {
        while (i <= j && ((arr[i] & (1 << bit)) == 0))
        {
            i++;
        }

        while (i <= j && ((arr[j] & (1 << bit)) != 0))
        {
            j--;
        }

        if (i <= j)
        {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;

            i++;
            j--;
        }
    }

    radixExchangeSort(arr, left, j, bit - 1);

    radixExchangeSort(arr, i, right, bit - 1);
}

int main()
{
    int arr[] = {10, 7, 5, 2, 12, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("original array : \n");
    printarr(arr,n);
    int maxBit = getMaxBit(arr, n);

    radixExchangeSort(arr, 0, n - 1, maxBit);
    printf("Sorted array : \n");
    printarr(arr,n);

    return 0;
}