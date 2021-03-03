#include <stdio.h>
#include <unistd.h>

/* Lecture 16: Lab Exercise
   Program: sleeper.c

   This program, in conjunction with libmylib.so.1.0.1 (source mylib.c)
   demonstrates how easy it is to use the environment variable:
   LD_PRELOAD set to your own malicious code in your own malicious
   library to do some very nasty stuff. This program simply calls the
   sleep() funciton defined in <unistd.h>; however, because libmylib
   has a sleep function that doesn't do what you would expect, and
   because the LD_PRELOAD environment variable was set to load my nasty
   little library first, bang! You have been compromised!

   Results when running this in various ways:
   1) as a regular program LD_PRELOAD set
      a) my dirty litlle sleep() function is called
   2) as a Set-UID root program LD_PRELOAD set
      a) the usual sleep() function is called because LD_PRELOAD is
         not set in root's environment
      b) we are not calling the system() function where the shell
         environment from which the program is executed is copied
         to the child process
   3) run as root with LD_PRELOAD set to my nasty little library
      a) my nasty little sleep() function get called
*/

int main(int argc, char **argv)
{
    printf("Going to sleep now...\n");
    sleep(1);

    return 0;
}
