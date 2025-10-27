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
    } else if (WIFSTOPPED(wstatus)){
        printf("stop signal: %d\n", WSTOPSIG(wstatus));
    } else if (WIFCONTINUED(wstatus)){
        printf("child continued\n");
    }
}

int main(int argc, char* argv[])
{
    pid_t pid = fork();

    switch (pid){
    case -1:
        error(1, errno, "fork");
    case 0:
        printf("child: pid = %d\n", getpid());
        for(;;);
        /* exit(18); */
        /* abort(); */
        break;
    default:
        int wstatus;
        /* pid_t child = waitpid(pid, &wstatus, WNOHANG); */
        /* pid_t child = waitpid(pid, &wstatus, WUNTRACED | WCONTINUED); */
        pid_t child = waitpid(pid, &wstatus, WCONTINUED);
        if (child > 0){
        printf("child %d terminated\n", child);
        print_wstatus(wstatus);
        } else if (child == 0){
            printf("no child terminated\n");
        }
        else {
            error(1, errno, "waitpid");
        }
    }
    return 0;

}

