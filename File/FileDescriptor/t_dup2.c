#include "func.h"

int main(int argc, char* argv[])
{
    int oldfd = open("app.log", O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (oldfd == -1){
        error(1, errno, "open");
    }

    printf("oldfd = %d\n", oldfd);

    write(STDERR_FILENO, "FIRST error message\n", 20);


    int newfd = dup2(oldfd, STDERR_FILENO);
    if (newfd == -1){
        error(1, errno, "dup");
    }

    printf("newfd = %d\n", newfd);

    write(STDERR_FILENO, "Second error message\n", 21);
    
    close(oldfd);
    close(newfd);
    return 0;
}

