#include "func.h"

int main(int argc, char* argv[])
{
    printf("Hello ");

    pid_t pid = fork();
    
    switch(pid){
    case -1:
        error(1, errno, "fork");
    case 0:
        //child
        printf("child: I am a babay\n");
        break;
    default:
        //parent
        printf("parent: Who is your daddy?\n");
        break;
    }

    return 0;
}

