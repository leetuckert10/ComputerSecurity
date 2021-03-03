#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Lecture 16: Lab Exercise
   Program: catWrap.c

   This program demonstrates a very real problem with using system()
   from within another program. Since this one prompts the user for a
   file to cat and since this program is purposely designed to provide
   the ability to cat, but not modify any file, it has a major flaw
   if cat is called with system(). System() uses a shell to execute
   commands and since the shell is able to stack commands using a
   ';' between commands, all you have to do when specifying the file
   name is this: ./catWrap "/etc/shadow;rm /etc/boo". The file will
   be removed! This is not a problem with execve(). It does not execute
   commands in a shell.
*/

int main(int argc, char** argv)
{
    char *v[3];
    char *command;

    if (argc < 2) {
        printf("Please type a file name.\n");
        return 1;
    }

    v[0] = "/bin/cat";
    v[1] = argv[1];
    v[2] = NULL;

    command = malloc(strlen(v[0]) + strlen(argv[1]) + 2);
    sprintf(command, "%s %s", v[0], argv[1]);

    // Use on one of the following commenting out the other.
    // system(command);
    execve(v[0], v, NULL);  /* The safe way... */
    
    return 0;
}

