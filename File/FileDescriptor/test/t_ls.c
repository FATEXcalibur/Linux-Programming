#include "func.h"

// 改进1， 添加函数来格式化权限
void print_mode(mode_t mode){
    printf((S_ISDIR(mode)) ? "d" : "-");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");

}

int main(int argc, char* argv[])
{
    // ./t_ls filename
    
    ARGS_CHECK(argc, 2);
    
    // 1. get fd
    int fd = -1;
    if ((fd = open(argv[1], O_RDONLY)) == -1){
        error(1, errno, "open %s\n", argv[1]);
    }
    
    struct stat st;
    if (fstat(fd, &st) == -1){
        error(1, errno, "fstat");
    }

    
    printf("size = %ld, mode = %o, inode = %ld, c_time = %ld\n", 
           st.st_size, 
           st.st_mode, 
           st.st_ino, 
           st.st_ctim.tv_sec);

    close(fd);
    
    return 0;
}

