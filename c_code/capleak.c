#include <string.h>
#include <fcntl.h>      // file handling
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     // execve

/* Lecture 14: Capability Leaking
   Program: capleak.c

   This program demonstrates what is known as a capability leak. The
   file descriptor obtained the euid is root is passed to the shell
   that is created as just a plain user. Yet, if you type:
   echo bbbbbb >&3 (the file descripter value printed fromt the
   program), you can actually write to the file as an ordinary user
   even though the permissions on the file are root only.
*/

int main(int argc, char** argv)
{
    int fd;
    char *v[2];         // an array of pointers
    
    // Make sure this file exists and is owned by root in group root
    // and has 644 permissions.
    fd = open("/etc/zzz", O_RDWR | O_APPEND);
    if (fd == -1) {
        printf("Cannot open /etc/zzz\n");
        exit(0);
    }

    printf("fd is %d\n", fd);   // Have fun with this in the shell.

    setuid(getuid());   // we can now drop our special permissions.

    v[0] = "/bin/sh";
    v[1] = 0;
    // Open file descripter passed right on to this shell.
    execve(v[0], v, 0);

    return 0;
}

