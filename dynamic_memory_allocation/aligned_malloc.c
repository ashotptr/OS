#include <stdio.h>
#include <stdlib.h>

int is_power_of_two(size_t number) {
    if (number == 0) {
        return 0;
    }
    while (number != 1) {
        if (number % 2 != 0) {
            return 0;
        }
        number = number / 2;
    }
    return 1;
}

void* aligned_malloc(size_t size, size_t alignment) {
    if (!is_power_of_two(alignment)) {
        printf("Error: Alignment must be a power of 2.\n");
        return NULL;
    }

    size_t total_size = size + alignment + sizeof(void*);
    void* unaligned_ptr = malloc(total_size);

    if (unaligned_ptr == NULL) {
        return NULL;
    }

    size_t start_address = (size_t)unaligned_ptr + sizeof(void*);
    size_t remainder = start_address % alignment;
    size_t padding = 0;

    if (remainder != 0) {
        padding = alignment - remainder;
    }
    
    void* aligned_ptr = (void*)(start_address + padding);
    ((void**)aligned_ptr)[-1] = unaligned_ptr;

    return aligned_ptr;
}

void aligned_free(void *ptr) {
    if (ptr == NULL) {
        return;
    }
    void* unaligned_ptr = ((void**)ptr)[-1];
    free(unaligned_ptr);
}

int main() {
    size_t size = 100;
    size_t alignment = 64;

    printf("Requesting %zu bytes with %zu-byte alignment.\n\n", size, alignment);
    
    void *ptr = aligned_malloc(size, alignment);
    
    if (ptr != NULL) {
        printf("Aligned pointer: %p\n", ptr);
        
        if ((size_t)ptr % alignment == 0) {
            printf("Success! The pointer is correctly aligned.\n");
        } else {
            printf("Failure! The pointer is NOT aligned.\n");
        }

        void* original_ptr = ((void**)ptr)[-1];
        printf("Original malloc ptr: %p\n", original_ptr);

        aligned_free(ptr);
        printf("\nMemory has been freed.\n");

    } else {
        printf("aligned_malloc failed.\n");
    }
    
    return 0;
}
