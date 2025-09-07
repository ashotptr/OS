#include <stdio.h>

int main() {
    int arr[5] = {10, 20, 30, 40, 50};

    int *ptr = arr;
    
    for (int i = 0; i < 5; i++) {
        printf("Element at index %d: %d\n", i, *(ptr + i));
    }

    for (int i = 0; i < 5; i++) {
        *(ptr + i) = (i + 1) * 100;
    }
    
    for (int i = 0; i < 5; i++) {
        printf("Element at index %d: %d\n", i, *(ptr + i));
    }
    
    for (int i = 0; i < 5; i++) {
        printf("Element at index %d: %d\n", i, arr[i]);
    }

    return 0;
}