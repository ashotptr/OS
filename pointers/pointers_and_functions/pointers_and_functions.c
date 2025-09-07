#include <stdio.h>

int swap(int* a, int* b){
    int c = *a;
    *a = *b;
    *b = c;
}

int main(){
    int a = 1;
    int b = 2;
    printf("Value of a before: %d\nValue of b before: %d", a, b);

    swap(&a, &b);

    printf("Value of a after: %d\nValue of b after: %d", a, b);

    return 0;
}
