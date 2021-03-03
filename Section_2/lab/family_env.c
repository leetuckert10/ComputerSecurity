#include <string.h>
#include <fcntl.h>      // file handling
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     // execve

/* Lecture 16: Lab Exercise
   Program: family_env.c

   This program demonstrates that when a process is forked, the child
   process gets a copy of every environment variable that exists in the
   parent process. By running the program with the call to printenv()
   commented out for parent and then for child and sending the output
   to different files in each case, it is proven that the content of
   both files will be identical.
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
    pid_t childPid;

    switch (childPid = fork()) {
        case 0:         // This is the child process.
            // printenv();
            exit(0);
        default:        // This is the parent process.
            printenv();
            exit(0);
    }

    return 0;
}

