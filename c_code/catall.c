#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* Lecture 13: Attacks via Explict User Inputs
   Program: catall.c
   This program will only work correctly if /bin/sh is linked to
   /bin/zsh. If sh is linked to dash, there is a countermearure built
   in to prevent other programs from being executed with set-UID.

   This program assumes that you have: sudo chown root catall and,
   sudo chmod 4755 catall.

   This program is intended to be executed as in:
   ./catall "some_file;/bin/sh"

   If you have linked the shell as stated above, and if you have put
   the whole argument string in double quotes, you will be granted
   a root shell! Have fun!

   The fundamental problem with this program is that it is mixing data
   with code, the data being, user input that might be quite malicious
   in nature...
*/

int main(int argc, char** argv)
{
    char *cat = "/bin/cat";

    if (argc < 2) {
        printf("Please type a file name.\n");
        return 1;
    }

    char *command = malloc(strlen(cat) + strlen(argv[1]) + 2);
    sprintf(command, "%s %s", cat, argv[1]);
    system(command);
    
    return 0;
}

