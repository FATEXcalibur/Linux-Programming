#include "func.h"

int main(int argc, char* argv[])
{
    pid_t pid = fork();

    switch(pid){
    case -1:
        error(1, errno, "fork");
    case 0:
        sleep(1);
        printf("pid = %d, ppid = %d\n", getpid(), getppid());
    default:
        exit(0);
    }
    return 0;
}

