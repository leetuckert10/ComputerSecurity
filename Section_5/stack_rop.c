/* Vunlerable program: stack.c */
/* You can get this program from the lab's website */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Changing this size will change the layout of the stack.
 * Instructors can change this value each year, so students
 * won't be able to use the solutions from the past.
 * Suggested value: between 0 and 400  */
#ifndef BUF_SIZE
#define BUF_SIZE 24
#endif

/* Compilation instructions:
   1.   gcc -DBUF_SIZE=<N> -o bin/stack -z execstack -fno-stack-protector
            stack.c
   2.   sudo chown root bin/stack
   3.   sudo chmod 4755 bin/stack
   4.   Make sure the "badfile" is in the bin directory.
   5.   Generate "badfile" with exploit.c.
*/

int bof(char *str)
{
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

    // The following statement has a buffer overflow problem.
    strcpy(buffer, str);       

    return 1;
}

/* For the purpose of experimentation. */
void bar()
{
    static int i = 0;
    printf("Fucntion bar() is invoked %d times!\n", ++i);
}

int main(int argc, char **argv)
{
    char str[518];
    FILE *badfile;

     /* Change the size of the dummy array to randomize the parameters
        for this lab. Need to use the array at least once */
    char dummy[BUF_SIZE];  memset(dummy, 0, BUF_SIZE);

    badfile = fopen("badfile", "r");
    fread(str, sizeof(char), 517, badfile);

    bof(str);
    printf("Returned Properly\n");

    return 1;
}
