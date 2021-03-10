#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* This program demonstrates how easy it is to get a string, like a 
   program name, into memory and the the address of the string location.
   All of this is part of engineering a return to libc attack.

   1.   Compile: gcc -o env55 envaddr.c
   2.   If we were using this program in conjunction with the vulnerable
        program, stack, we have to have the length of this program name
        to be exactly the same length as the stack program name. ??

   The reason the length of the program name is significant is because
   the executing program name is also on the stack frame above the space
   where environment variables are stored; therefore, a program name with
   a different length will cause the address on MYSHELL to be slightly
   different.
*/
int main(int argc, char **argv)
{
    char *shell = (char *) getenv("MYSHELL");

    if (shell) {
        printf("  Value: %s\n", shell);
        // The commented out printf was in course code. Mine works as well.
        // printf("Address: %x\n", (unsigned int) shell);
        printf("Address: %p\n", shell);
    }
}
