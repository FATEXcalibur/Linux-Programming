#include "func.h"

int main(int argc, char *argv[])
{
    // ./t_rmdir path
    if (argc != 2){
        error(1, 0, "Usage: %s path", argv[0]);
    }

    if (rmdir(argv[1]) == -1){
        error(1, errno, "rmdir");
    }

    return 0;
}

