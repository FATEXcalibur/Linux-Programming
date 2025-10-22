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

}

void copyDir(const char* src, const char* dst){
    //创建dst目录
    if (mkdir(dst, 0776)){
        error(1, errno, "mkdir");
    }

    //打开src目录
    DIR* srcDir = opendir(src);
    if (srcDir){
        error(1, errno, "opendir");
    }

    //遍历目录流
    errno = 0;
    while (struct dirent* curr = readdir(srcDir)){
        const char* filename = curr->d_name;
        // 忽略.和..
        if(filename[0] == '.'){
            continue;
        }

        //如果该目录项是目录，则调用copyDir递归复制
        if (curr->d_type == DT_DIR){
            char newSrcDir[MAXSIZE];
            char newDstDir[MAXSIZE];
            sscanf(newSrcDir, "%s/%s", src, filename);
            sscanf(newDstDir, "%s/%s", dst, filename);
            copyDir(newSrcDir, newDstDir);
        }
        //如果改目录项是文件，则调用copyFile复制文件
        if (curr->d_type == DT_REG){
            char newSrc[MAXSIZE];
            char newDst[MAXSIZE];
            sscanf(newSrc, "%s/%s", src, filename);
            sscanf(newDst, "%s/%s", dst, filename);
            copyFile(newSrc, newDst);
        }
    }

    if(errno){
        error(1, errno, "readdir");
    }
}

