#include "func.h"

int main(int argc, char *argv[])
{

    printf("pid = %d, ppid = %d\n", getpid(), getppid());

    printf("Begin\n");

    const char* arguments[] = {"echoall", "aaa", "bbb", "ccc", NULL};
    const char* envp[] = {"USER=calibur", "KEY=value", NULL};
    /* execve("echoall", arguments, envp); */
    /* execl("./echoall", "./echoall", "aaa", "bbb", "cccc", NULL); */

    /* execlp("echoall", "./echoall", "aaa", "bbb", "cccc", NULL); */

    execle("echoall", "aaaa", "bbb", NULL, envp);
    printf("Can you see me?\n");
    error(1, errno, "exeve");
    return 0;
}

