#include "func.h"

int simple_system(const char* command){
    pid_t childPid = fork();
    int status;

    switch (childPid){
    case -1:
        return -1;
    case 0:
        execl("bin/sh", "sh", "-c", command, NULL);
        _exit(127);
    default:
        if (waitpid(childPid, &status, 0) == -1){
            return -1;
        } else {
            return status;
        }
    }
}

int main(int argc, char *argv[])
{
    simple_system("ls | wc");
    return 0;
}

