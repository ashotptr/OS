#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    int *arr;
    double sum = 0.0;
    double average;
    int i;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    arr = (int *)calloc(n, sizeof(int));

    if (arr == NULL) {
        printf("Error! Memory not allocated.\n");
        return 1;
    }

    printf("Array after calloc: ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Enter %d integers: ", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    printf("Updated array: ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    for (i = 0; i < n; i++) {
        sum = sum + arr[i];
    }

    if (n > 0) {
        average = sum / n;
        printf("Average of the array: %.1f\n", average);
    } else {
        printf("Cannot calculate average of 0 elements.\n");
    }

    free(arr);

    return 0;
}
