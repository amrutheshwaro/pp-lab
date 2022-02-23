#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

void merge(int a[], int low, int mid, int high) {
    int b[1000], i = low, k = low, j = mid + 1;
    while (i <= mid && j <= high)
        b[k++] = a[i] <= a[j] ? a[i++] : a[j++];
    while (i <= mid)
        b[k++] = a[i++];
    while (j <= high)
        b[k++] = a[j++];
    for (k = low; k <= high; k++)
        a[k] = b[k];
}

void mergesort(int a[], int low, int high) {
    int mid = low + (high - low)/2;
    if (low < high) {
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                mergesort(a, low, mid);
            }
            #pragma omp section
            {
                mergesort(a, mid + 1, high);
            }
        }
        merge(a, low, mid, high);
    }
}

void main() {
    int n, i;
    printf("Enter the number of elements to be randomly generated.\n");
    scanf("%d", &n);
    int a[n];
    printf("The randomly generated elements are.\n");
    for (i = 0; i < n; i++) {
        a[i] = rand() % 1000;
        printf("%d\t", a[i]);
    }
    printf("\n");
    mergesort(a, 0, n-1);
    printf("The sorted array is\n");
    for (i = 0; i < n; i++)
        printf("%d\t", a[i]);
    printf("\n");
}