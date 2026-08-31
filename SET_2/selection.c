#include<stdio.h>

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void selection_sort(int arr[],int n){
    int i , j , min_index;
    for(i=0;i<n;i++){
        min_index=i;
        for(j=i+1;j<n;j++){
            if (arr[j]<arr[min_index]){
                min_index=j;
            } 
        }
        if(min_index!=i){
            swap(&arr[i],&arr[min_index]);
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
    int arr[]={5,7,2,9,4,6};
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("original array : \n");
    printarr(arr,n);

    selection_sort(arr,n);
    printf("Sorted array : \n");
    printarr(arr,n);

    return 0;


}