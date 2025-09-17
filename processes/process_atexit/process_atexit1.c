#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void cleanup_function_1()
{
    printf("--- Cleanup function 1 called ---\n");
}

void cleanup_function_2()
{
    printf("--- Cleanup function 2 called ---\n");
}

int main()
{
    printf("Program starting.\n");

    atexit(cleanup_function_1);
    printf("Register cleanup_function_1\n");

    atexit(cleanup_function_2);
    printf("Register cleanup_function_2\n");

    printf("Main logic finished. Program will now terminate normally.\n");
    exit(0);

    return 0;
}
