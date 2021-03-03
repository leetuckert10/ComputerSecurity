#include <string.h>
#include <fcntl.h>      // file handling
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     // execve

/* Lecture 16: Lab Exercise
   Program: leaker.c

   This program demonstrates what is known as a capability leak. The
   file descriptor obtained the when euid is root and then not closed
   before the root privilege is revoked (line 29), leaves the child
   process the ability to write anything at all to a file that it does
   not have permission to write to!
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

    sleep(1);           // simulate work
    setuid(getuid());   // we can now drop our special permissions.

    if (fork()) {       // parent process
        close(fd);
        exit(0);
    } else {            // child process
        write(fd, "Malicious Data\n", 15);
        close(fd);
    }

    return 0;
}

