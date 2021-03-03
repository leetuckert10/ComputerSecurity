#include <string.h>
#include <fcntl.h>      // file handling
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     // execve

/* Lecture 16: Lab Exercise
   Program: lsWrap.c

   This program, in conjunction with my own version of 'ls', clearly
   demonstrates how easy it is to modify an environment variable that
   causes system() to execute arbritary code with root privilege. To
   set this up:
   1) compile this file
   2) complie ls.c
   3) sudo chown root ls
   4) sudo chmod 4755 ls
   5) make sure that /bin/sh is not linked to dash which has a
      build countermeasure; link it to zsh
   6) from your regular shell execute:
      export PATH=`pwd`:$PATH
   7) ./lsWrap
   8) the ls progam in this directory will be executed which cats
      /etc/shadow.
*/

int main(int argc, char **argv)
{
    system("ls");

    return 0;
}

