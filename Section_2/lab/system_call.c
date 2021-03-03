#include <fcntl.h>      // file handling
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>     // execve

/* Lecture 16: Lab Exercise
   Program: system_call.c

   This program demonstrates that the system() call actually uses
   /bin/sh -c <command> throuh the system calls execl() which actually
   calls execve() with the environmen varialbes array as the third
   argument.

   Compile and run this with the call to execve() commented out. Then,
   compile and run with the call to system() commented out and the call
   to execve() uncommented. You will see that the output is identical.
*/

extern char **environ;

int main(int argc, char** argv)
{
    char *v[2];
    
    v[0] = "/usr/bin/env";
    v[1] = '\0';

    // system("/usr/bin/env");
    execve("/usr/bin/env", v, environ);

    return 0;
}

