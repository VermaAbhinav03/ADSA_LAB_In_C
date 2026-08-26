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

int main(){
    int arr[]={4,5,73,2,1,8};
    int n = sizeof(arr)/sizeof(arr[0]);
    for (int i = 0; i < n; i++){
      printf("%d ", arr[i]);  
    }
    printf("\n");

    bubbleSort(arr, n);

    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    return 0;


}