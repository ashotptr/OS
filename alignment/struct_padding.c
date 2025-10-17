#include <stdio.h>
#include <stddef.h>

struct UnorderedStruct {
    char   a;
    int    b;
    double c;
};

struct OrderedStruct {
    double c;
    int    b;
    char   a;
};

int main() {
    struct UnorderedStruct u_instance;

    printf("--- Unordered Struct (char, int, double) ---\n");
    printf("Size of the struct: %zu bytes\n", sizeof(struct UnorderedStruct));

    printf("Address of struct instance: %p\n", (void *)&u_instance);
    printf("Address of char 'a':        %p\n", (void *)&(u_instance.a));
    printf("Address of int 'b':         %p\n", (void *)&(u_instance.b));
    printf("Address of double 'c':      %p\n", (void *)&(u_instance.c));
    printf("\n");

    struct OrderedStruct o_instance;

    printf("--- Ordered Struct (double, int, char) ---\n");
    printf("Size of the struct: %zu bytes\n", sizeof(struct OrderedStruct));
    
    printf("Address of struct instance: %p\n", (void *)&o_instance);
    printf("Address of double 'c':      %p\n", (void *)&(o_instance.c));
    printf("Address of int 'b':         %p\n", (void *)&(o_instance.b));
    printf("Address of char 'a':        %p\n", (void *)&(o_instance.a));
    printf("\n");

    return 0;
}
