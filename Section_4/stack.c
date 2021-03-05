#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/*
Below is all the commands and various OS tweaks to get this program to
demonstrate buffer overflow.

# This turns of countermeasure: memory randomization.
$ sudo sysctl -w kernel.randomize_va_space=0
$ kernel.randomize_va_space = 0

# Compilation
$ gcc -z execstack -fno-stack-protector -o stack stack.c
$ sudo chown root stack
$ sudo chmod 4755 stack
$ ls -al        # just checking it...

# Execution (1st time)
$ head -c 100 /dev/urandom > badfile
$ ./stack       # returns properly
$ head -c 160 /dev/urandom > badfile
$ ./stack       # puke; green chunks, smelly
$ Segmentation fault

This sections is for lecture 28...
# Compilation with debugging symbols.
$ gcc -z execstack -fno-stack-protector -g -o stack_dbg stack.c
$ touch badfile
$ gdb -q stack_dbg      # -q means "quiet"
gdb-peda$
gdb-peda$ b foo         # set a breakpoint at foo()
Breakpoint 1 at 0x80484c1: file stack.c, line 11.
gdb-peda$ run
gdb-peda$ p $ebp
$1 = (void *) 0xbfffeb88
gdb-peda$ p &buffer
$2 = (char (*)[100]) 0xbfffeb1c
gdb-peda$ p/d 0xbfffeb88 - 0xbfffeb1c
$3 = 108
gdb-peda$ quit

*/

int foo(char *str)
{
    char buffer[100];

    // The following statement has a buffer overflow problem.
    strcpy(buffer, str);
    
    return 1;
}

int main(int argc, char **argv)
{
    char str[400];
    FILE *badfile;

    badfile = fopen("badfile", "r");
    fread(str, sizeof(char), 300, badfile);
    foo(str);

    printf("foo() return properly...\n");
    
    return 1;
}
