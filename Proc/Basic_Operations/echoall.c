#include "func.h"

int main(int argc, char *argv[])
{
    printf("pid = %d, ppid = %d\n", getpid(), getppid());

    printf("CommandLine Arguments: \n");
    for (int i = 0; i < argc; ++i){
        printf("    %s\n", argv[i]);
    }

    printf("Environment Variables: \n");
    extern char** environ;
    char** p = environ;
    
    while (*p != NULL){
        printf("    %s\n", *p);
        p++;
    }

    return 0;
}

