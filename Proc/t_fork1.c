#include "func.h"

int main(int argc, char* argv[])
{
    printf("begin\n");

    pid_t pid = fork();

    switch (pid){
    case -1:
        error(1, errno, "fork");
    case 0:
        // child
        printf("pid = %d, ppid = %d\n", getpid(), getppid());
        printf("child: I am a baby\n");
        break;
    default:
        // parent
        printf("parent: pid = %d, child = %d\n", getpid(), pid);
        printf("Parent: Who's your daddy?\n");
        break;
    }
    return 0;
}

