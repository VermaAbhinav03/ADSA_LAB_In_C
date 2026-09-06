#include <stdio.h>

#define MAX 100

void printarr(int arr[] , int SIZE){
    for(int i=0;i<SIZE;i++){
        printf("%d \t",arr[i]);
    }
    printf("\n");
}

void merge(int arr[], int left, int mid, int right)
{
    int temp[MAX];

    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
        {
            temp[k] = arr[i];
            i++;
        }
        else
        {
            temp[k] = arr[j];
            j++;
        }

        k++;
    }

    while (i <= mid)
    {
        temp[k] = arr[i];
        i++;
        k++;
    }

    while (j <= right)
    {
        temp[k] = arr[j];
        j++;
        k++;
    }

    for (i = left; i <= right; i++)
    {
        arr[i] = temp[i];
    }
}

void mergeSort(int arr[], int n)
{
    int size;
    int left;
    int mid;
    int right;

    for (size = 1; size < n; size = size * 2)
    {

        for (left = 0; left < n - 1; left = left + 2 * size)
        {
            mid = left + size - 1;
            right = left + 2 * size - 1;

            if (mid >= n)
                continue;

            if (right >= n)
                right = n - 1;

            merge(arr, left, mid, right);
        }
    }
}

int main() {

    int arr[]={5,7,2,9,4,6};
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("original array : \n");
    printarr(arr,n);

    mergeSort(arr,n);

    printf("Sorted array : \n");
    printarr(arr,n);

    return 0;
}
