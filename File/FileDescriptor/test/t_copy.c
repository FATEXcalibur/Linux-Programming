#include "func.h"

#define MAXSIZE 4096

int main(int argc, char* argv[])
{
    // ./t_copy source_file dest_file
    // 1. check args
    ARGS_CHECK(argc, 3);
    
    // 2. get fd
    int srcfd = open(argv[1], O_RDONLY);
    if (srcfd == -1){
        error(1, errno, "open");
    }

    /* int destfd = open(argv[2], O_WRONLY | O_CREAT, 0666); */
    // 改进：目标权限应该与源文件保持相同，而不是固定0666
    struct stat st;
    if (fstat(srcfd, &st) == -1){
        error(1, errno, "stat %s", argv[1]);
    }
    int destfd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, st.st_mode);

    if (destfd == -1){
        error(1, errno, "open");
    }

    // 3. get content of src and write to dest
    int size;
    char buff[MAXSIZE];
    errno = 0;
    off_t total_size = st.st_size;
    off_t copied_size = 0;
    while ((size = read(srcfd, buff, MAXSIZE)) > 0){
        if (write(destfd, buff, size) == -1){
            error(1, errno, "write");
        }
        copied_size += size;
        if (total_size > 0){
            printf("\rProcess: %.1f%%\n", (double)copied_size * 100 / total_size);
        }
    } // EOF or error

    if (errno){
        error(1, errno, "read");
    }

    // 4. close fd
    close(destfd);
    close(srcfd);
    
    return 0;
}

