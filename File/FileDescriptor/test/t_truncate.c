#include "func.h"

int main(int argc, char* argv[])
{
    // ./t_truncate filename new_size
    
    ARGS_CHECK(argc, 3);

    // open file
    int fd = -1;
    if ((fd = open(argv[1], O_RDWR | O_CREAT, 0666)) == -1){
        error(1, errno, "open %s\n", argv[1]);
    }

    // truncate file
    off_t length;
    if (sscanf(argv[2], "%ld", &length) != 1){
        error(1, 0, "Invalid size: %s", argv[2]);
    }
   
    if (length < 0){
        error(1, 0, "Size cannot be negative");
    }

    if (ftruncate(fd, length) == -1){
        error(1, errno, "ftruncate %d\n", fd);
    }

    close(fd);
    return 0;
}

