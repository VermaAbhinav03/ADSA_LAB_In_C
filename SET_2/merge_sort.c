#include<stdio.h>

void printarr(int arr[] , int SIZE){
    for(int i=0;i<SIZE;i++){
        printf("%d \t",arr[i]);
    }
    printf("\n");
}


void merge(int arr[],int left,int mid,int right){

    int i=left,j=mid+1,k =left,temp[100];
    //int j=mid+1;
    //int k =left;
    //int temp[100];

    while (i<=mid && j<=right)
    {
        if(arr[i]<arr[j]){
            temp[k]=arr[i];
            i++;
        }
        else
        {
            temp[k]=arr[j];
            j++;
        }
        k++;
    }

    while (i<=mid)
    {
        temp[k]=arr[i];
        i++;
        k++;
    }
    
    while (j<=right)
    {
        temp[k]=arr[j];
        j++;
        k++;
    }
    
    for(i=left;i<=right;i++)
    {
        arr[i]=temp[i];
    }
     
}



void mergeSortRecursive(int arr[],int left,int right){
    if(left<right)
    {
    int mid = (left + right)/2;
    //printf("%d",mid);
    mergeSortRecursive(arr,left,mid);
    mergeSortRecursive(arr,mid+1,right);
    merge(arr,left,mid,right);
    }

}

int main(){
    int arr[]={5,7,2,9,4,6};
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("original array : \n");
    printarr(arr,n);

    mergeSortRecursive(arr,0,n-1);

    printf("Sorted array : \n");
    printarr(arr,n);

    return 0;
}