#include "func.h"

#define MAXSIZE 128

void copyFile(const char* src, const char* dst);
void copyDir(const char* src, const char* dst);

int main(int argc, char *argv[])
{
    // ./t_cp dir1 dir2
    
    ARGS_CHECK(argc, 3);
    copyDir(argv[1], argv[2]);
   
    return 0;
}

void copyFile(const char* src, const char* dst){
    // 复制文件
    // create new file of dst
    int dstfd = open(dst, O_RDWR | O_CREAT, 0664);
    
    if (dstfd == -1){
        error(1, errno, "open dstfd failed");
    }

    int srcfd = open(src, O_RDONLY);
    
    if (srcfd == -1){
        error(1, errno, "open srcfd failed");
    }
    // copy srcfd to dstfd
    errno = 0;
    char buff[MAXSIZE];
    int bytes = 0;
    while ((bytes = read(srcfd, buff, MAXSIZE)) > 0){
        if(write(dstfd, buff, bytes) == -1){
            error(1, errno, "write");
        }
    } //-1 or EOF
    
    if (errno){
        error(1, errno, "read");
    }
    
    // close
    close(dstfd);
    close(srcfd);
}

void copyDir(const char* src, const char* dst){
    //创建dst目录
    if (mkdir(dst, 0776)){
        error(1, errno, "mkdir");
    }

    //打开src目录
    DIR* srcDir = opendir(src);
    if (srcDir == NULL){
        error(1, errno, "opendir");
    }

    //遍历目录流
    errno = 0;
    struct dirent* curr;
    while (curr = readdir(srcDir)){
        const char* filename = curr->d_name;
        // 忽略.和..
        if(filename[0] == '.'){
            continue;
        }

        for (int i = 0; i < 4; ++i){
            putchar(' ');
        }

        puts(filename);

        //如果该目录项是目录，则调用copyDir递归复制
        if (curr->d_type == DT_DIR){
            char newSrcDir[MAXSIZE];
            char newDstDir[MAXSIZE];
            sprintf(newSrcDir, "%s/%s", src, filename);
            sprintf(newDstDir, "%s/%s", dst, filename);
            copyDir(newSrcDir, newDstDir);
        }
        //如果改目录项是文件，则调用copyFile复制文件
        if (curr->d_type == DT_REG){
            char newSrc[MAXSIZE];
            char newDst[MAXSIZE];
            sprintf(newSrc, "%s/%s", src, filename);
            sprintf(newDst, "%s/%s", dst, filename);
            copyFile(newSrc, newDst);
        }
    }

    if(errno){
        error(1, errno, "readdir");
    }
}

