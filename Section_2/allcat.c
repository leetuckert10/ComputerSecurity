#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Lecture 13: Attacks via Explict User Inputs
   Program: allcat.c

   So, this program is much, much better because it uses execve(). 
   execve() separates the code to execute from the data that might be
   entered by a user. The system() function uses a shell to execute
   the command. The shell, being very powerful, is what, in the previous
   example, two commands to be executed back to back by the simple
   insertion of a ';" between the commands. execve does not use a shell
   to execute it's commands. The system shell can even be affected by
   the definition of environment variables. In the system function, the
   shell program is the middle man and having a middle man is NEVER a
   good thing. When using execev, the semi-colon has not special meaning
   at all unlike the shell.
*/

int main(int argc, char** argv)
{
    char *v[3];

    if (argc < 2) {
        printf("Please type a file name.\n");
        return 1;
    }

    v[0] = "/bin/cat";
    v[1] = argv[1];
    v[2] = '\0';

    execve(v[0], v, 0);

    return 0;
}

