#include <stdio.h>
#include <stdlib.h>

void main()
{
    char x[12];                             // goes on the stack
    char *y = malloc(sizeof(char) * 12);    // goes on the heap

    printf("Address of stack buffer 'x': %p\n", x);
    printf(" Address of heap buffer 'y': %p\n", y);

    free(y);
}

