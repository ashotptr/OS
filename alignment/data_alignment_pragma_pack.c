#include <stdio.h>

struct DefaultStruct {
    char   a;
    int    b;
    double c;
};

#pragma pack(1)
struct PackedStruct1 {
    char   a;
    int    b;
    double c;
};

#pragma pack(2)
struct PackedStruct2 {
    char   a;
    int    b;
    double c;
};

#pragma pack(4)
struct PackedStruct4 {
    char   a;
    int    b;
    double c;
};

#pragma pack()

int main() {
    struct DefaultStruct d_instance;
    printf("--- Default Alignment ---\n");
    printf("Size of struct: %zu bytes\n", sizeof(d_instance));
    printf("Address of char 'a':   %p\n", (void *)&(d_instance.a));
    printf("Address of int 'b':    %p\n", (void *)&(d_instance.b));
    printf("Address of double 'c': %p\n", (void *)&(d_instance.c));
    printf("\n");

    struct PackedStruct1 p1_instance;
    printf("--- #pragma pack(1) ---\n");
    printf("Size of struct: %zu bytes\n", sizeof(p1_instance));
    printf("Address of char 'a':   %p\n", (void *)&(p1_instance.a));
    printf("Address of int 'b':    %p\n", (void *)&(p1_instance.b));
    printf("Address of double 'c': %p\n", (void *)&(p1_instance.c));
    printf("\n");

    struct PackedStruct2 p2_instance;
    printf("--- #pragma pack(2) ---\n");
    printf("Size of struct: %zu bytes\n", sizeof(p2_instance));
    printf("Address of char 'a':   %p\n", (void *)&(p2_instance.a));
    printf("Address of int 'b':    %p\n", (void *)&(p2_instance.b));
    printf("Address of double 'c': %p\n", (void *)&(p2_instance.c));
    printf("\n");

    struct PackedStruct4 p4_instance;
    printf("--- #pragma pack(4) ---\n");
    printf("Size of struct: %zu bytes\n", sizeof(p4_instance));
    printf("Address of char 'a':   %p\n", (void *)&(p4_instance.a));
    printf("Address of int 'b':    %p\n", (void *)&(p4_instance.b));
    printf("Address of double 'c': %p\n", (void *)&(p4_instance.c));
    printf("\n");

    return 0;
}
