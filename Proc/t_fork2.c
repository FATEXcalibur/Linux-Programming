#include "func.h"

int g_value = 1; //数据段
int main(int argc, char* argv[])
{
    int l_value = 2; // 栈

    int *p = (int*)malloc(sizeof(int)); //堆
    *p = 3;

    pid_t pid = fork();
    
    switch(pid){
    case -1:
        error(1, errno, "fork");
    case 0:
        //child
        g_value *= 8;
        l_value *= 8;
        *p *= 8;
        printf("child: g_value = %d, l_value = %d, *p = %d\n", 
               g_value, l_value, *p);
        break;
    default:
        //parent
        sleep(3);
        printf("child: g_value = %d, l_value = %d, *p = %d\n", 
               g_value, l_value, *p);
        break;
    }

    return 0;
}

