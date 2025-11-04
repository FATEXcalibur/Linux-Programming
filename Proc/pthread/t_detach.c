#include "func.h"

void* start_routine(void*){
    sleep(3);
    return NULL;
}

int main(int argc, char* argv[])
{
    pthread_t tid;
    int err = pthread_create(&tid, NULL, start_routine, NULL);
    if (err){
        error(1, err, "pthread_create");
    }

    pthread_detach(tid);
    err = pthread_join(tid, NULL);
    if (err) {
        error(1, err, "pthread_join");
    }

    printf("main thread: 0x%lx terminated\n", tid);

    return 0;
}

