#include "func.h"

void print_ids(const char* prefix){
    printf("%s: pid = %d, ppid = %d, tid = 0x%lx\n",
           prefix, 
           getpid(),
           getppid(), 
           pthread_self());
}

int main(int argc, char *argv[])
{
    print_ids("main thread");
    return 0;
}

