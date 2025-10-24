#include "func.h"


int main(int argc, char* argv[]){
    // ./t_fstat file
    if (argc != 2){
        error(1, 0, "Usage: %s file", argv[0]);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1){
        error(1, errno, "open");
    }

    struct stat statbuf;
    if (fstat(fd, &statbuf) == -1){
        error(1, errno, "fstat");
    }

    close(fd);

    printf("st_ino = %lld, st_mode = %o, st_nlinks = %u, st_size = %ld, st_blocks = %ld\n",
         (long long)statbuf.st_ino, 
         statbuf.st_mode, 
         statbuf.st_nlink, 
         statbuf.st_size, 
         statbuf.st_blocks 
         );
    return 0;
}
