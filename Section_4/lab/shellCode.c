#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* This program was compiled into assembly language and is stored in bin:
   To compile:
   1.  gcc -S -o shellCode shellCode.c
   2.  gcc -m32 -masm=intel -c shellCode.s -o shellCode.o
   3.  gcc -m32 shellCode.o -o shellCode
*/

int main (int argc, char **argv)
{
    char *name[2];
    name[0] = "/bin/sh";
    name[1] = '\0';

    execve(name[0], name, '\0');

    return 0;
}
