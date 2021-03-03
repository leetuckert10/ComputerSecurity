#include <string.h>
#include <fcntl.h>      // file handling
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     // execve

/* Lecture 16: Lab Exercise
   Program: setUID.c

   This program demonstrates one of the big dangers of Set-UID
   programs. Compile this and change the owner to root. Then use
   chmod 4755 to change the pemissions setting the Set-UID bit. 
   Now, set some sort of environment in your shell, not a root shell,
   your shell. Note that the variable you set makes its way into
   a program executing with root privilege. Dangerous, very dangerous.
*/

extern char **environ;

void printenv()
{
    int i = 0;
    while (environ[i] != NULL) {
        printf("%s\n", environ[i++]);
    }
}

int main(int argc, char** argv)
{
    printenv();

    return 0;
}

