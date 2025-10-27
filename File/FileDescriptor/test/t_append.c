#include "func.h"

int main(int argc, char* argv[])
{
    // ./append filename content
    // check argc
    ARGS_CHECK(argc, 3);

    // get fd
    int fd = -1;
    if ((fd = open(argv[1], O_WRONLY | O_CREAT, 0666)) == -1){
        error(1, errno, "open %s", argv[1]);
    }

    // move position of file
    if (lseek(fd, 0, SEEK_END) == -1){
        error(1, errno, "lseek");
    }

    if (write(fd, argv[2], strlen(argv[2])) == -1){
        error(1, errno, "write");
    }

    close(fd);
    return 0;
}

