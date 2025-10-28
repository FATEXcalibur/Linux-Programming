#include "func.h"

#define MAXRAGS 128
#define MAXLINE 1024

void print_wstatus(int status){
    if (WIFEXITED(status)){
        printf("Exit code: %d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)){
        printf("Terminate signal: %d\n", WTERMSIG(status));
#ifdef WCOREDUMP
        if (WCOREDUMP(status)){
            printf("(core dumped)");
        }
#endif
        printf("\n");
    }
}

void parse_parameter(char* message, char* argv[]){
    int i = 0;
    argv[i] = strtok(message, " \n\t");

    while (argv[i]){
        i++;
        argv[i] = strtok(NULL, " \t\n");
    }
}

int main(int argc, char *argv[])
{
    char cmd[MAXLINE];
    char* parameters[MAXRAGS];
    int status;

    for(;;){
        printf("%s", "SimpleShell > ");
        // get user command
        fgets(cmd, MAXLINE, stdin);
        // cmd exit, termiate
        if (strcmp(cmd, "exit\n") == 0){
            exit(0);
        }

        //fork 
        pid_t pid = fork();

        switch (pid) {
        case -1:
            error(1, errno, "fork");
        case 0:
            // parsing command
            parse_parameter(cmd, parameters);
            if (execvp(parameters[0], parameters) == -1){
                error(1, errno, "execvp");
            }
            break;
        default:
            if (waitpid(pid, &status, 0) == -1){
                error(1, errno, "waitpid");
            }
            printf("%d terminated\n", pid);
            print_wstatus(status);
        }
    }
    return 0;
}

