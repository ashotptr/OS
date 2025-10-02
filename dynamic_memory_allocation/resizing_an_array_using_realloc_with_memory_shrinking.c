#include <stdio.h>
#include <stdlib.h>

int main() {
    int n_initial = 10;
    int *arr = (int *)malloc(n_initial * sizeof(int));

    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Enter 10 integers: ");
    for (int i = 0; i < n_initial; i++) {
        scanf("%d", &arr[i]);
    }

    int n_resized = 5;
    int *resized_arr = (int *)realloc(arr, n_resized * sizeof(int));

    if (resized_arr == NULL) {
        printf("Memory reallocation failed!\n");
        free(arr);
        return 1;
    }
    
    arr = resized_arr;

    printf("Array after resizing: ");
    for (int i = 0; i < n_resized; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);

    return 0;
}
