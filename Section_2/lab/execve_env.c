#include <fcntl.h>      // file handling
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>     // execve

/* Lecture 16: Lab Exercise
   Program: execve_env.c

   This program demonstrates that calling execve with a null pointer
   array for the enviroment (3 arg), will produce no output from env.
   However, if you pass the environment array of strings as the third
   argument, then you will get a page full of defined environment
   variables.
*/

extern char **environ;

int main(int argc, char** argv)
{
    char *v[2];
    
    v[0] = "/usr/bin/env";
    v[1] = '\0';

    // execve("/usr/bin/env", v, '\0');
    execve("/usr/bin/env", v, environ);

    return 0;
}

