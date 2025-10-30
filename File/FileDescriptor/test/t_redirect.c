#include "func.h"

int main(int argc, char* argv[])
{
    // ./t_redirect filename command
    ARGS_CHECK(argc, 3);

    // open fd of filename
    int fd = -1;
    if ((fd = open(argv[1], O_RDWR | O_CREAT, 0666)) == -1){
        error(1, errno, "open %s\n", argv[1]);
    }

    // fork
    pid_t childPid = fork();
    int status;

    switch (childPid){
    case -1:
        error(1, errno, "fork");
    case 0:
        // child
        // 重定向
        if (dup2(fd, STDOUT_FILENO) == -1){
            error(1, errno, "dup2 %d %d\n", fd, STDOUT_FILENO);
        }


        break;
    default:
        // parent
    }
    return 0;
}

