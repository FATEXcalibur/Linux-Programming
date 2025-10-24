#include "func.h"

int main(int argc, char* argv[]){
    // ./t_ftruncate file length
    if (argc != 3){
        error(1, 0, "Usage: %s file length", argv[0]);
    }

    int fd = open(argv[1], O_WRONLY);
    if (fd == -1){
        error(1, errno, "open");
    }

    int length;
    sscanf(argv[2], "%d", &length);

    if (ftruncate(fd, length) == -1){
        error(1, errno, "ftruncate");
    }

    return 0;
}
