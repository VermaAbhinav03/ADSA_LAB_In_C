#include <stdio.h>

void swap(int* a,int* b){
    int temp;
    temp= *a;
    *a=*b;
    *b=temp;
}

void bubbleSort(int arr[], int n){
    for(int i=0; i<n-1; i++){
        for(int j=0;j<n-1-i; j++){
            if (arr[j]>arr[j+1]){
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

void printarr(int arr[] , int SIZE){
    for(int i=0;i<SIZE;i++){
        printf("%d \t",arr[i]);
    }
    printf("\n");
}

int main(){
    int arr[]={4,5,73,2,1,8};
    int n = sizeof(arr)/sizeof(arr[0]);

    printf("original array : \n");
    printarr(arr,n);

    bubbleSort(arr, n);

    printf("Sorted array : \n");
    printarr(arr,n);

    return 0;


}