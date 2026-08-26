#include<stdio.h>

void swap(int arr[] , int j , int k){
             int temp = arr[j];
             arr[j] = arr[k];
             arr[k] = temp;
}

void selectionSort(int arr[] , int n){
     
    for(int i = 0 ;i<n ;i++){
        int min = i;
        for(int j = i+1 ; j < n ;j++){
            if(arr[min] > arr[j]){
                min = j;
            }
        }
        swap(arr,i,min);
    }

}

int main(){
    int arr[] = {9,8,7,5,4,3,2,7,1};
    int n = sizeof(arr)/sizeof(arr[0]);
    selectionSort(arr,n);

    for(int i = 0 ;i< n ; i++){
        printf("%d ",arr[i]);
       }
    return 0;
}