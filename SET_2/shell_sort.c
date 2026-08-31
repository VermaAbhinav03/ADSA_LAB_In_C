#include<stdio.h>

void printarr(int arr[] , int SIZE){
    for(int i=0;i<SIZE;i++){
        printf("%d \t",arr[i]);
    }
    printf("\n");
}

void shell_sort(){

}

int main(){
    int arr[]={5,7,2,9,4,6};
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("original array : \n");
    printarr(arr,n);

    insertion_sort(arr,n);
    
    printf("Sorted array : \n");
    printarr(arr,n);

    return 0;

}