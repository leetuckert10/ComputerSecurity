#include <stdio.h>

/* Lecture 16: Lab Exercise
   Program: mylibc.c

   Compile this program as a shared library:
   gcc -fPIC -g -c mylib.c

   The above creates an object file.

   Next, create a shared library:
   gcc -shared -o libmylib.so.1.0.1 mylib.o -lc

   See comments in sleeper.c.
*/

void sleep(int s)
{
    printf("Hey fool! I am not sleeping!\n");
}
