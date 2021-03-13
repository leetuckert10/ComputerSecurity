#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Changing this size will change the layout of the stack.
 * Instructors can change this value each year, so students
 * won't be able to use the solutions from the past.
 * Suggested value: between 0 and 200 (cannot exceed 300, or
 * the program won't have a buffer-overflow problem). */
#ifndef BUF_SIZE
#define BUF_SIZE 12
#endif

int bof(FILE *badfile)
{
    /*********************************************************************
     *  This is a discussion regarding what the stack frame for bof()
     *  is built:
     *  1.  When bof() is called, the return address of this fucntion
     *      is pushed on to the stack frame for bof() by the call
     *      instruction (ebp + 8).
     *  2.  The first function prolog instruction is to save the caller's
     *      stack frame (ebp) into the previous ebp field (ebp + 4).
     *  3.  The second instruction moves the current stack position (esp)
     *      into the frame pointer (ebp). ebp always points to the
     *      beginning of the address of the old ebp value.
     *  4.  The third instruction moves the esp value by N bytes to allow
     *      space for local variables.
     *
     *  The function epilogue restores the stack to it's initial state.
     *  1.  The first instruction sets the stack pointer (esp) to the
     *      value of the frame pointer (ebp). This effectively releases
     *      the stack space allocated for the local variables.
     *  2.  The second instruction pops (assigns) the previous frame
     *      pointer value into ebp. At this point the stack state is
     *      exactly the same as it was at the beginning.
     *  3.  The final instruction pops the return address from the stack
     *      and then jumps to it. The instruction also moves the stack
     *      pointer (esp) and the memory space storing the return address
     *      is freed.
     *********************************************************************/
    char buffer[BUF_SIZE];
    unsigned int *framep;
    char *shell = (char *) getenv("MYSHELL");

    asm("movl %%ebp, %0" : "=r" (framep));

    // Print out information we need.
    printf("Address of buffer[]: 0x%.8x\n", (unsigned) buffer);
    printf("Frame Pointer value: 0x%.8x\n", (unsigned) framep);

    if (shell) {
        printf("The '%s' string address is %p.\n", shell, shell);
    }

    printf("The offset between ebp start and buffer start is: %d\n",
            (unsigned) framep - (unsigned) buffer);

    /* Using fread() to read the data from the file directly into the
       buffer circumvents the problem of have a '\0' byte in the string
       which is the case in using strcpy(). strcpy will stop copying
       when it runs across a null byte thinking it is the end of the
       string. */
    fread(buffer, sizeof(char), 300, badfile);

    return 1;
}

int main(int argc, char **argv)
{
    FILE *badfile;

    /* Change the size of the dummy array to randomize the parameters
       for this lab. Need to use the array at least once */
    char dummy[BUF_SIZE * 5];  memset(dummy, 0, BUF_SIZE * 5);

    badfile = fopen("badfile", "r");
    bof(badfile);

    printf("Returned Properly\n");
    fclose(badfile);
    return 1;
}
