#include "func.h"

void print_ids(const char* prefix){
    printf("%s: pid = %d, ppid = %d, tid = 0x%lx\n",
           prefix,
           getpid(), 
           getppid(), 
           pthread_self());
}

struct foo {
    int a;
    int b;
    int c;
};

void* start_routine(void* args){
    print_ids("new thread");
    struct foo* x = (struct foo*)args;
    printf("new thread: x = {%d, %d, %d}\n",
           x->a, x->b, x->c);
    return NULL;
}

int main(int argc, char *argv[])
{
    print_ids("main thread");
    //create new thread
    pthread_t tid; //output argument
    struct foo x = {1, 2, 3};

    int err = pthread_create(&tid,  NULL, start_routine, &x);
    if (err) {
        error(1, err, "pthread_create");    // pthread: return error code, not set errno
    }
    
    printf("main thread: create a thread 0x%lx\n", tid);

    sleep(3);
    return 0;   //exit(0): exit会导致进程退出， 所有线程都会终止
}

