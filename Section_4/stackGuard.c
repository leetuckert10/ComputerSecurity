#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void foo(char *arg)
{
    char buffer[12];
    // Buffer overflow vulnerability.
    strcpy(buffer, arg);
    printf("string '%s' is %d bytes long\n", buffer, strlen(buffer));
}

int main (int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: %s <some string>\n", argv[0]);
        return 1;
    }

    foo(argv[1]);
    printf("foo() returned normally\n");

    return 0;
}
