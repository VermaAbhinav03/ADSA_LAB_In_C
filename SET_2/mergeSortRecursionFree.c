#include <stdio.h>

#define MAX 100

void printarr(int arr[] , int SIZE){
    for(int i=0;i<SIZE;i++){
        printf("%d \t",arr[i]);
    }
    printf("\n");
}

struct Node {
    int left;
    int right;
    int step;
};

struct Node stack[MAX];
int top = -1;

void push(int left, int right, int step) {
    top++;

    stack[top].left = left;
    stack[top].right = right;
    stack[top].step = step;
}

struct Node pop() {
    return stack[top--];
}

void merge(int arr[], int left, int mid, int right) {
    int temp[MAX];

    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k] = arr[i];
            i++;
        } else {
            temp[k] = arr[j];
            j++;
        }
        k++;
    }

    while (i <= mid) {
        temp[k] = arr[i];
        i++;
        k++;
    }

    while (j <= right) {
        temp[k] = arr[j];
        j++;
        k++;
    }

    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }
}

void mergeSort(int arr[], int n) {

    push(0, n - 1, 0);

    while (top != -1) {

        struct Node current = pop();

        int left = current.left;
        int right = current.right;
        int step = current.step;

        if (left >= right)
            continue;

        int mid = (left + right) / 2;

        if (step == 0) {

            push(left, right, 2);

            push(mid + 1, right, 0);

            push(left, mid, 0);
        }
        else {

            merge(arr, left, mid, right);
        }
    }
}

int main() {

    int arr[]={5,7,2,9,4,6};
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("original array : \n");
    printarr(arr,n);

    mergeSort(arr,n);

    printf("Sorted array : \n");
    printarr(arr,n);

    return 0;
}
