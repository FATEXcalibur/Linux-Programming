#include "func.h"

#define MAXSIZE 10

int main(int argc, char *argv[])
{
    /* char buf[MAXSIZE]; */
    char *cwd = getcwd(NULL, 0);

    if(cwd == NULL){
        error(1, errno, "getcwd");
    }

    puts(cwd);
    free(cwd);
    return 0;
}

