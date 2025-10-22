#include "func.h"

int main(int argc, char *argv[])
{
    // ./t_readdir dir
    if (argc != 2){
        error(1, 0, "Usage: %s dir", argv[0]);
    }

    //1. 打开目录流
    DIR * stream = opendir(argv[1]);
    if (!stream) {
        error(1, errno, "opendir");
    }

    //2. 依次读取每一个目录项
    errno = 0;
    struct dirent* curr; //当前读取的目录项
    while ((curr = readdir(stream)) != NULL){
        //读取了目录项
        //打印目录项的成员
        printf("d_ino = %lld, d_off = %lld, d_reclen = %hu d_type = %d, d_name = %s\n", (long long)curr->d_ino
               , (long long)curr->d_off
               , curr->d_reclen
               , curr->d_type
               , curr->d_name);
    }//curr == NULL
    
    if (errno){
        error(1, errno, "readdir");
    }

    closedir(stream);
    return 0;
}

