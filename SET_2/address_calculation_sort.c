#include <stdio.h>
#include <stdlib.h>

void printarr(int arr[] , int SIZE){
    for(int i=0;i<SIZE;i++){
        printf("%d \t",arr[i]);
    }
    printf("\n");
}

void addressCalculationSort(int arr[], int n)
{
    int min = arr[0];
    int max = arr[0];

    for (int i = 1; i < n; i++)
    {
        if (arr[i] < min)
            min = arr[i];

        if (arr[i] > max)
            max = arr[i];
    }

    int range = max - min + 1;
    int *count = (int *)calloc(range, sizeof(int));

    for (int i = 0; i < n; i++)
    {
        int address = arr[i] - min;
        count[address]++;
    }

    int k = 0;

    for (int i = 0; i < range; i++)
    {
        while (count[i] > 0)
        {
            arr[k] = i + min;
            k++;
            count[i]--;
        }
    }

    free(count);
}

int main()
{
    int arr[] = {23, 12, 45, 18, 31, 13, 45};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("original array : \n");
    printarr(arr,n);

    addressCalculationSort(arr, n);

    printf("Sorted array : \n");
    printarr(arr,n);

    return 0;
}
