#include "func.h"


int main(int argc, char* argv[]){
    /* int fd = open("a.txt", O_RDWR | O_CREAT | O_TRUNC, 0666); */
    int fd = open("b.txt", O_RDWR | O_CREAT, 0666);
    if (fd == -1){
        error(1, errno, "open");
    }

    printf("fd = %d\n", fd);
    return 0;
}
