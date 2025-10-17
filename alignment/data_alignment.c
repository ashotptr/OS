#include <stdio.h>

int main() {
    char myChar;
    short myShort;
    int myInt;
    double myDouble;
    
    printf("--- Data Type Sizes ---\n");
    printf("Size of char:   %zu byte(s)\n", sizeof(char));
    printf("Size of short:  %zu byte(s)\n", sizeof(short));
    printf("Size of int:    %zu byte(s)\n", sizeof(int));
    printf("Size of double: %zu byte(s)\n", sizeof(double));
    printf("\n");
    
    printf("--- Variable Memory Addresses ---\n");
    printf("Address of myChar:   %p\n", (void *)&myChar);
    printf("Address of myShort:  %p\n", (void *)&myShort);
    printf("Address of myInt:    %p\n", (void *)&myInt);
    printf("Address of myDouble: %p\n", (void *)&myDouble);
    printf("\n");

    return 0;
}
