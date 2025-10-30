#include "func.h"

#define MAXLINE 1024

int main(int argc, char* argv[])
{
    int fd1 = open("pipe1", O_RDONLY);
    if (fd1 == -1){
        error(1, errno, "open pipe1 failed");
    }

    int fd2 = open("pipe2", O_WRONLY);
    if (fd2 == -1){
        error(1, errno, "open pipe2 failed");
    }

    printf("Established!\n");

    // 点对点聊天
    // 设置感兴趣的I/O事件
    fd_set mainfds; //放置感兴趣的文件描述符

    FD_ZERO(&mainfds);
    FD_SET(STDIN_FILENO, &mainfds);

    int maxfds = STDIN_FILENO;
    FD_SET(fd1, &mainfds);
    if (fd1 > maxfds){
        maxfds = fd1;
    }
    
    char rcvline[MAXLINE];
    char sndline[MAXLINE];

    for (;;){
        fd_set readfds = mainfds;
        int nready = select(maxfds + 1, &readfds, NULL, NULL, NULL);
        switch (nready){
        case -1:
            error(1, errno, "select");
        case 0:
            printf("TIMEOUT\n");
            break;
        default:
            //轮询
            if (FD_ISSET(STDIN_FILENO, &readfds)){
                //stdin 就绪
                if (fgets(sndline, MAXLINE, stdin) != NULL){
                    write(fd2, sndline, strlen(sndline) + 1);
                }
            }

            if (FD_ISSET(fd1, &readfds)){
                // 管道就绪
                int nbytes = read(fd1, rcvline, MAXLINE);
                if (nbytes > 0){
                    printf("From p2: %s", rcvline);
                } else if (nbytes == 0){
                    goto end;
                } else {
                    error(1, errno, "read");
                }
            }
            break;
        }
    }
end:
    close(fd1);
    close(fd2);
    return 0;
}

