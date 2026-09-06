#include<stdio.h>

void printarr(int arr[] , int SIZE){
    for(int i=0;i<SIZE;i++){
        printf("%d \t",arr[i]);
    }
    printf("\n");
}

void swap(int *a,int *b){
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}

int partition(int arr[],int low,int high){
    int pivot=arr[high];
    int i=low-1;
    for(int j=low;j<=high-1;j++){
        if (arr[j]<pivot){
            i++;
            swap(&arr[i],&arr[j]);
        }
    }
    swap(&arr[i+1],&arr[high]);
    return i+1;
}

void quickSortRecursive(int arr[],int low,int high){
    if (low<high){
        int pivot_index=partition(arr,low,high);
        quickSortRecursive(arr,low,pivot_index-1);
        quickSortRecursive(arr,pivot_index+1,high);
    }
}



int main(){
    int arr[]={5,7,2,9,4,6};
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("original array : \n");
    printarr(arr,n);

    quickSortRecursive(arr,0,n-1);

    printf("Sorted array : \n");
    printarr(arr,n);

    return 0;
}