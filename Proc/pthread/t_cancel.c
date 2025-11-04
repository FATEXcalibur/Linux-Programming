#include "func.h"

void* start_routine(void*){
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

    for(;;){
        /* sleep(1); */
    }

    return NULL;
}

int main(int argc, char* argv[])
{
    pthread_t tid;
    int err = pthread_create(&tid, NULL, start_routine, NULL);
    if (err){
        fprintf(stderr, "pthread_create failed");
        pthread_exit(NULL);
    }

    sleep(3);

    err = pthread_cancel(tid);
    if (err){
        fprintf(stderr, "pthread_cancel failed");
        pthread_exit(NULL);
    }

    void* retval;
    pthread_join(tid, &retval);
    if (retval == PTHREAD_CANCELED){
        printf("0x%lx canceled\n", tid);    // 唯一方式，判断是否取消线程
    }

    return 0;

}

