#include "func.h"

int main(int argc, char* argv[])
{
    // ./t_safe_write filename content

    ARGS_CHECK(argc, 3);

    // open file
    int fd = -1;
    if ((fd = open(argv[1], O_RDWR | O_APPEND | O_CREAT, 0666)) == -1){
        error(1, errno, "open %s\n", argv[1]);
    }

    // write content
    if (write(fd, argv[2], strlen(argv[2])) == -1){
        error(1, errno, "write %s\n", argv[1]);
    }

    // sync to disk
    if (fsync(fd) == -1){
        error(1, errno, "fsync %d\n", fd);
    }

    return 0;
}

