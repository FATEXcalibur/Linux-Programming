#include "func.h"

typedef struct{
    int a;
    int b;
    int c;
} Foo;

void* start_routine(void*){
    /* sleep(3); */
    // Foo x = {1, 2, 3};
    Foo *x = (Foo*)malloc(sizeof(Foo));
    x->a = 1;
    x->b = 2;
    x->c = 3;
    return (void*)x;
}
int main(int argc, char* argv[])
{
    pthread_t tid;
    int err = pthread_create(&tid, NULL, start_routine, NULL);
    if (err){
        error(1, err, "pthread_create");
    }

    Foo*  retval;
    pthread_join(tid, (void**)&retval);

    printf("main thread: retval = {%d, %d, %d}\n",
           retval->a, retval->b, retval->c);

    free(retval);
    return 0;

}

