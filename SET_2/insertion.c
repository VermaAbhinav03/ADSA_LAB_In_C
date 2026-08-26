#include<stdio.h>

void insertionSort(int arr[] , int n){
    for(int i = 0 ;i< n ;i++){
        int key = arr[i];
        int j = i;
        while(j>0 && key < arr[j-1]){
            arr[j] = arr[j-1];
            j--;
        }

        arr[j] = key;
    }
}


int main(){
    int arr[] = {9,8,7,5,4,3,2,7,1};
    int n = sizeof(arr)/sizeof(arr[0]);
    insertionSort(arr,n);

    for(int i = 0 ;i< n ; i++){
        printf("%d ",arr[i]);
       }
    return 0;
}