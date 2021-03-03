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
*/

int main(int argc, char **argv)
{
    printf("Going to sleep now...\n");
    sleep(1);
}
