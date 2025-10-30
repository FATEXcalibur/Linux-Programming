#include "func.h"

#define MAXLINE 1024

int main(int argc, char* argv[])
{
    int fields[2];
    // create pipe
    if (pipe(fields) == -1){
        error(1, errno, "pipe");
    }

    // fields[0]: read filed[1]: write
    write(fields[1], "Hello pipe\n", 11);
    char message[MAXLINE];
    read(fields[0], message, MAXLINE);
    printf("message: %s", message);
    return 0;
}

