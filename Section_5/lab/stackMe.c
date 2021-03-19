#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int foo()
{
    unsigned int *framep;
    unsigned int *stackp;

    asm("movl %%ebp, %0" : "=r" (framep));
    asm("movl %%esp, %0" : "=r" (stackp));

    // Print out information we need.
    printf("Frame Pointer (ebp): 0x%.8x\n", (unsigned) framep);
    printf("Stack Pointer (esp): 0x%.8x\n", (unsigned) stackp);
    printf("The offset between ebp and esp is %d bytes\n",
            (unsigned) framep - (unsigned) stackp);

    return 1;
}

int main(int argc, char **argv)
{
    foo();
    return 1;
}
