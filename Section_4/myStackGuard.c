#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* Show how to prevent StackGuard by writing smart-ass code. */

void foo(char *arg)
{
    char *buffer;
    buffer = (char *) calloc(strlen(arg) + 1, sizeof(char));
    strcpy(buffer, arg);
    printf("String '%s' is %d bytes long\n", buffer, strlen(buffer));
    free(buffer);
}

void fubar(char *arg)
{
    char buffer[12];
    if (strlen(arg) > 12) {
        printf("Buffer overflow dude!\n");
        return;
    }
    strcpy(buffer, arg);
    printf("String '%s' is %d bytes long\n", buffer, strlen(buffer));
}

int main (int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: %s <some string>\n", argv[0]);
        return 1;
    }

    foo(argv[1]);
    printf("foo() returned normally\n");

    fubar(argv[1]);
    printf("fubar() returned normally\n");

    return 0;
}
