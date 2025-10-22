#include <stdio.h>
#include <error.h>
#include <unistd.h>
#include <errno.h>

#define MAXSIZE 128

int main(int argc, char *argv[])
{
    //1.校验参数
    if (argc != 2){
        error(1, 0, "Usage: %s path", argv[0]);
    }

    //2. 打印当前工作目录
    char cwd[MAXSIZE];
    getcwd(cwd, MAXSIZE);
    puts(cwd);

    //3. change current work dir
    if (chdir(argv[1])){
        // 发生了错误
        error(1, errno, "chdir");
    }

    // no err
    getcwd(cwd, MAXSIZE);
    puts(cwd);

    return 0;
}

