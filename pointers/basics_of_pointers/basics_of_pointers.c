#include <stdio.h>

int main()
{
    int a = 1;

    int* b = &a;

    printf("Address via a: %p \nAddress via b: %p \n", &a, b);

    *b = 4;
    
    printf("Value via a: %d \nValue via b: %d \n", a, *b);

    return 0;
}
