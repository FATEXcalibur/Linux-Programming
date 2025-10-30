#include "func.h"

void func1(void){
    printf("func1");
}

void func2(void){
    printf("func2");
}

int main(int argc, char* argv[])
{
    // 注册退出处理函数
    atexit(func1);
    atexit(func2);
    atexit(func2);


    // 执行
    printf("Begin\n");

    printf("I am going to die...");
    exit(0);
    return 0;
}

