#include <stdio.h>

#define BUCKETS 5
#define BUCKET_SIZE 20

void printarr(int arr[] , int SIZE){
    for(int i=0;i<SIZE;i++){
        printf("%d \t",arr[i]);
    }
    printf("\n");
}

void insertionSort(int bucket[], int size)
{
    for (int i = 1; i < size; i++)
    {
        int key = bucket[i];
        int j = i - 1;

        while (j >= 0 && bucket[j] > key)
        {
            bucket[j + 1] = bucket[j];
            j--;
        }

        bucket[j + 1] = key;
    }
}

void bucketSort(int arr[], int n)
{
    int buckets[BUCKETS][BUCKET_SIZE] = {0};
    int bucketCount[BUCKETS] = {0};

    // Step 1: Put elements into buckets
    for (int i = 0; i < n; i++)
    {
        int index = arr[i] / 10;

        buckets[index][bucketCount[index]] = arr[i];
        bucketCount[index]++;
    }

    // Step 2: Sort each bucket
    for (int i = 0; i < BUCKETS; i++)
    {
        insertionSort(buckets[i], bucketCount[i]);
    }

    // Step 3: Combine buckets
    int k = 0;

    for (int i = 0; i < BUCKETS; i++)
    {
        for (int j = 0; j < bucketCount[i]; j++)
        {
            arr[k] = buckets[i][j];
            k++;
        }
    }
}

int main()
{
    int arr[] = {29, 25, 3, 49, 9, 37, 21, 43};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("original array : \n");
    printarr(arr,n);

    bucketSort(arr,n);

    printf("Sorted array : \n");
    printarr(arr,n);

    return 0;
}
