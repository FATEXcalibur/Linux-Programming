#include "func.h"

int main(int argc, char *argv[])
{
    printf("errno = %d\n", errno);

    FILE* fp = fopen("not_exist.txt", "r");

    printf("errno = %d\n", errno);
    fprintf(stderr, "errno = %d\n", errno);
    fprintf(stderr, "%s\n", strerror(errno));
    perror("not_exist.txt");

    const char* prefix = "not_exist.txt";
    fprintf(stderr, "%s: %s\n", prefix, strerror(errno));

    error(1, errno, "not_exist.txt");

    return 0;
}

