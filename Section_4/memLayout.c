#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* This program just shows where various program components are stored
   in program memory.

   Notes:
   - You can compile a C program into assembly code by using the -S
     option on gcc: gcc -S -o blah blah.c
*/

int x = 100;        // data segment of memmory due to initialization 

/* When this function is called a new block of memory will be allocated
   - on top of the stack. It is called a stack frame.
   - top section contains function arguments
   - next section contains return function return address; this return
     address is the address of the next line in the code after the
     function call
   - next section contains previous stack frame pointer
   - bottom section contains local function variables
*/

void func(int a, int b, int *ptr)
{
    int ans;        // stored in local variable section of stack

    ans = a + b;
    ptr[0] = ans;   // value is stored on the heap
    ans = a - b;
    ptr[1] = ans;   // value is stored on the heap
}

void copyFunc()
{
    /* Demonstrates how strcpy relies on the null byte to end it's copy
       operation. */
    char *src = "This is a str\0ing to copy.";
    char *dest = (char *) calloc(strlen(src) + 1, sizeof(char));
    strcpy(dest, src);
    printf("Note that strcpy() will stop when it finds the null byte.\n");
    printf("%s\n", dest);
}

int main(int argc, char **argv)
{
    int a = 5;      // in the stack
    int b = 2;      // in the stack
    static int y;   // in BSS (unitialized static/global variables)
    int *ptr;       // in stack because is a local variable

    /* Memory is allocated in heap where dynamic memory allocation is
       handled. */
    ptr = (int *) malloc(2 * sizeof(int));

    func(a, b, ptr);    // a new stack frame is created

    printf("Program shows where program components are stored.\n");
    printf("a = %d, b = %d, ptr[0] = %d, ptr[1] = %d\n", a, b, ptr[0],
            ptr[1]);
    free(ptr);

    copyFunc();

    return 1;
}
