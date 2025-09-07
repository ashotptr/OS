#include <stdio.h>

int main() {
    int a = 1;

    int* ptra = &a;

    int** ptrptra = &ptra;

    printf("Value of a using ptra: %d\nValue of a using ptrptra: %d", *ptra, **ptrptra);
    
    return 0;
}