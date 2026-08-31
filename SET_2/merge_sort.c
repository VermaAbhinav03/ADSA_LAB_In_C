#include<stdio.h>

void printarr(int arr[] , int SIZE){
    for(int i=0;i<SIZE;i++){
        printf("%d \t",arr[i]);
    }
    printf("\n");
}


void merge(int arr[],int temp[],int mid,int left,int right){

     

    // Copy the merged, sorted elements back into the original array
    for ( int i = left; i <= right; i++) {
        arr[i] = temp[i];
    }
}



mergeSortRecursive(int arr[],int temp[], int left , int right){
    int mid = left + (right-left)/2;
    mergeSortRecursive(arr,temp,left,mid);
    mergeSortRecursive(arr,temp,mid+1,right);

    merge(arr,temp,mid,left,right);
}


void mergeSort(int arr[], int n) {

    int *temp = (int *)malloc(n * sizeof(int));
    if (temp != NULL) {
        mergeSortRecursive(arr, temp, 0, n - 1);
        free(temp); // Clean up the memory when the whole sort is done
    }
}



int main(){
    int arr[]={5,7,2,9,4,6};
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("original array : \n");
    printarr(arr,n);

    mergeSort(arr,n);

    printf("Sorted array : \n");
    printarr(arr,n);

    return 0;


}