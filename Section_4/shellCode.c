#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* This program shows how you can declare a function pointer this is
   actually just a buffer with machine language instructions in it and
   it will run a shell!
   Has to be compiled with execstack as in:
   gcc -z execstack -o bin/shellCode shellCode.c
*/

const char code [] =
    "\x31\xc0\x50\x68//sh\x68/bin"
    "\x89\xe3\x50\x53\x89\xe1\x99"
    "\xb0\x0b\xcd\x80";

int main (int argc, char **argv)
{
    char buffer[sizeof(code)];

    strcpy(buffer, code);

    // This creates a function pointer of buffer and executes it in
    // the stack!
    ((void(*) ()) buffer)();

    return 0;
}
