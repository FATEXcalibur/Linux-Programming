#include "func.h"

void func1(int status, void* args){
    printf("func1: status = %d\n", status);
    char* message = (char*)args;
    printf("func1: message = %s\n", message);
}

void func2(int status, void* args){
    printf("func2: status = %d\n", status);
    char* message = (char*)args;
    printf("func2: message = %s\n", message);
}

int main(int argc, char* argv[])
{
    // 注册退出处理函数
    on_exit(func1, (void*)"messageA");
    on_exit(func2, (void*)"messageB");
    on_exit(func2, (void*)"messageC");


    // 执行
    printf("Begin\n");

    printf("I am going to die...");
    exit(0);
    return 0;
}

