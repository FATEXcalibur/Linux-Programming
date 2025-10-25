#include "func.h"

#define MAXSIZE 128

void deleteDir(const char* path);

int main(int argc, char* argv[])
{
    // ./deleteDir dir
    ARGS_CHECK(argc, 2);

    deleteDir(argv[1]);
    return 0;
}

void deleteDir(const char* path){
    //打开目录
    DIR* pdir = opendir(path);
    if (!pdir){
        error(1, errno, "opendir %s", path);
    }

    // 遍历目录流, 依次删除每一个目录项
    struct dirent* pdirent;
    while((pdirent = readdir(pdir)) != NULL){
        //忽略.和..
        const char* filename = pdirent->d_name;

        if (!strcmp(filename, ".")){
            continue;
        }

        if (!strcmp(filename, "..")){
            continue;
        }
       
        //如果该目录项是目录，则调用deleteDir递归删除
        char newPath[MAXSIZE];
        sprintf(newPath, "%s/%s", path, filename);
 
        if (pdirent->d_type == DT_DIR){
            deleteDir(newPath);
        }
        // 如果该目录项是文件，则调用unlink删除文件
        if (pdirent->d_type == DT_REG){
            if(unlink(newPath)){
                error(1, errno, "unlink %s", newPath);
            }
        }
    }

    // 目录为空了，可以删除该目录了
    if(rmdir(path)){
        error(1, errno, "rmdir %s", path);
    }
    // 关闭目录流
    closedir(pdir);
}
