#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int INITIAL_SIZE = 3;
    int FINAL_SIZE = 5;
    int MAX_STRING_LENGTH = 50;
    char **string_array;
    int i;

    string_array = (char **)malloc(INITIAL_SIZE * sizeof(char *));
    if (string_array == NULL) {
        printf("Error! Could not allocate memory for the array of strings.\n");
        return 1;
    }

    for (i = 0; i < INITIAL_SIZE; i++) {
        string_array[i] = (char *)malloc(MAX_STRING_LENGTH * sizeof(char));
        if (string_array[i] == NULL) {
            printf("Error! Could not allocate memory for string #%d.\n", i + 1);
            while (--i >= 0) {
                free(string_array[i]);
            }
            free(string_array);
            return 1;
        }
    }

    printf("Enter 3 strings: ");
    
    for (i = 0; i < INITIAL_SIZE; i++) {
        scanf("%s", string_array[i]);
    }

    printf("Initial strings: ");
    for (i = 0; i < INITIAL_SIZE; i++) {
        printf("%s ", string_array[i]);
    }
    printf("\n");

    char **temp_ptr = (char **)realloc(string_array, FINAL_SIZE * sizeof(char *));
    
    if (temp_ptr == NULL) {
        printf("Error! Could not reallocate memory.\n");
        for (i = 0; i < INITIAL_SIZE; i++) {
            free(string_array[i]);
        }
        free(string_array);
        return 1;
    }
    
    string_array = temp_ptr;

    for (i = INITIAL_SIZE; i < FINAL_SIZE; i++) {
        string_array[i] = (char *)malloc(MAX_STRING_LENGTH * sizeof(char));
        if (string_array[i] == NULL) {
             printf("Error! Could not allocate memory for new string #%d.\n", i + 1);
             return 1;
        }
    }
    
    printf("Enter 2 more strings: ");
    for (i = INITIAL_SIZE; i < FINAL_SIZE; i++) {
        scanf("%s", string_array[i]);
    }

    printf("All strings: ");
    for (i = 0; i < FINAL_SIZE; i++) {
        printf("%s ", string_array[i]);
    }
    printf("\n");

    for (i = 0; i < FINAL_SIZE; i++) {
        free(string_array[i]);
    }
    
    free(string_array);

    return 0;
}
