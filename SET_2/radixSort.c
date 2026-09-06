#include<stdio.h>

void printarr(int arr[] , int SIZE){
    for(int i=0;i<SIZE;i++){
        printf("%d \t",arr[i]);
    }
    printf("\n");
}

void radixSort(int arr[], int n)
{
    int max = arr[0];

    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max)
            max = arr[i];
    }

    for (int place = 1; max / place > 0; place *= 10)
    {
        int output[n];
        int count[10] = {0};

        for (int i = 0; i < n; i++)
        {
            int digit = (arr[i] / place) % 10;
            count[digit]++;
        }

        int index = 0;

        for (int digit = 0; digit < 10; digit++)
        {
            for (int i = 0; i < n; i++)
            {
                int currentDigit = (arr[i] / place) % 10;

                if (currentDigit == digit)
                {
                    output[index] = arr[i];
                    index++;
                }
            }
        }

        for (int i = 0; i < n; i++)
        {
            arr[i] = output[i];
        }
    }
}

int main(){
    int arr[]={5,7,2,9,4,6};
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("original array : \n");
    printarr(arr,n);

    radixSort(arr,n);

    printf("Sorted array : \n");
    printarr(arr,n);

    return 0;
}