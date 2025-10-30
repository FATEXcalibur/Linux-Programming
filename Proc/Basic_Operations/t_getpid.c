#include "func.h"

int main(int argc, char* argv[])
{
    printf("pid = %d, ppid = %d\n", getpid(), getppid());
    for (;;);
    return 0;
}

