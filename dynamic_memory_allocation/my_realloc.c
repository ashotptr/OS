#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *my_realloc(void *ptr, size_t old_size, size_t new_size) {
    if (new_size == 0) {
        if (ptr != NULL) {
            free(ptr);
        }

        return NULL;
    }

    if (ptr == NULL) {
        return malloc(new_size);
    }

    void *new_ptr = malloc(new_size);

    if (new_ptr == NULL) {
        return NULL;
    }

    size_t copy_size = (old_size < new_size) ? old_size : new_size;

    memcpy(new_ptr, ptr, copy_size);

    free(ptr);

    return new_ptr;
}

void print_array(int *arr, int count, const char *label) {
    printf("%s (count %d): ", label, count);

    for (int i = 0; i < count; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");
}

int main() {
    int initial_count = 5;
    size_t old_size = initial_count * sizeof(int);
    int *arr = (int *)malloc(old_size);

    if (arr == NULL) return 1;

    for (int i = 0; i < initial_count; i++) {
        arr[i] = (i + 1) * 10;
    }

    print_array(arr, initial_count, "Original array");

    int grow_count = 10;
    size_t new_size_grow = grow_count * sizeof(int);
    int *temp_arr_grow = (int *)my_realloc(arr, old_size, new_size_grow);

    if (temp_arr_grow == NULL) {
        printf("Failed to grow the array.\n");

        free(arr);

        return 1;
    }

    arr = temp_arr_grow;
    old_size = new_size_grow;

    print_array(arr, grow_count, "Grown array ");

    int shrink_count = 3;
    size_t new_size_shrink = shrink_count * sizeof(int);
    int *temp_arr_shrink = (int *)my_realloc(arr, old_size, new_size_shrink);

    if (temp_arr_shrink == NULL) {
        printf("Failed to shrink the array.\n");

        free(arr);

        return 1;
    }

    arr = temp_arr_shrink;
    old_size = new_size_shrink;

    print_array(arr, shrink_count, "Shrunk array ");

    free(arr);

    return 0;
}
