#include "func.h"

void handler(int signo){
    switch (signo){
    case SIGINT:
        printf("Caught SINGINT\n");
        break;
    case SIGTSTP:
        printf("Caught SIGTSP\n");
        break;
    default:
        printf("Cauht UNKNOWN\n");
        break;
    }
}


int main(int argc, char *argv[])
{
    sighandler_t oldhandler = signal(SIGINT, handler);
    if (oldhandler == SIG_ERR){
        error(1, errno, "signal SIGINT");
    }
    oldhandler = signal(SIGTSTP, handler);
    if (oldhandler == SIG_ERR){
        error(1, errno, "signal SIGTSTP");
    }
    
    for(;;);
    return 0;
}

