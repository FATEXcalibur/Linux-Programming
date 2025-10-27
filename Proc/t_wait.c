#include "func.h"

void print_wstatus(int wstatus){
    if (WIFEXITED(wstatus)){
        printf("exit status: %d\n", WEXITSTATUS(wstatus));
    }else if (WIFSIGNALED(wstatus)){
        printf("termination signal: %d\n", WTERMSIG(wstatus));
#ifdef WCOREDUMP
        if (WCOREDUMP(wstatus)){
            printf("(core dump)");
        }
#endif
        printf("\n");
    }
}

int main(int argc, char* argv[])
{
    pid_t pid = fork();

    switch (pid){
    case -1:
        error(1, errno, "fork");
    case 0:
        /* for(;;); */
        /* exit(18); */
        abort();
        break;
    default:
        int wstatus;
        pid_t child = wait(&wstatus);
        printf("child %d terminated\n", child);
        print_wstatus(wstatus);
    }
    return 0;

}

