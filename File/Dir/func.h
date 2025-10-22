#ifndef _FUNC_H
#define _FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

#define ARGS_CHECK(argc, n) {   \
    if (argc != n){             \
        fprintf(stderr, "ERROR: expected %d arguments.\n", n);  \
        exit(1);                \
    }                           \
}

#define ERROR_CHECK(retval, val, msg){  \
    if(retval == val){                  \
        perror(msg);                    \
        exit(1);                        \
    }                                   \
}

#define SIZE(a) (sizeof(a) / sizeof(a[0]))

#endif
