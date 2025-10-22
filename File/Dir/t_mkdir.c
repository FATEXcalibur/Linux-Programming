#include "func.h"

int main(int argc, char *argv[])
{
    // ./t_mkdir path mode
    //
    if (argc != 3){
        error(1, 0, "Usage: %s path mode", argv[0]);
    }

    mode_t mode;
    sscanf(argv[2], "%o", &mode);
    if (mkdir(argv[1], mode)){
        error(1, errno, "mkdir");
    }

    return 0;
}

