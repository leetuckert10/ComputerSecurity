#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

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
