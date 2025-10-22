#include "func.h"

#define MAXSIZE 128

int main(int argc, char* argv[]){
    // ./t_chdir path
    // 1. 校验参数
    if (argc != 2){
        error(1, 0, "Usage: %s path", argv[0]);
    }

    // 2. 打印当前工作目录
    char cwd[MAXSIZE];
    getcwd(cwd, MAXSIZE);
    puts(cwd);

    // 3. 改变当前工作目录
    if (chdir(argv[1])){
        // error happened
        error(1, errno, "chdir");
    }

    // no error
    getcwd(cwd, MAXSIZE);
    puts(cwd);

    return 0;
}
