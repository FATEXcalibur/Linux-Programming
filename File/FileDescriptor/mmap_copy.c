#include "func.h"

#define MMAP_SIZE 4096 * 10

int main(int argc, char* argv[])
{
    // ./mmap_copy src dst
    
    if (argc != 3){
        error(1, 0, "usage: %s src dst", argv[0]);
    }

    int src = open(argv[1], O_RDONLY);
    if (src == -1){
        error(1, errno, "open %s failed", argv[1]);
    }

    int dst = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (dst == -1){
        error(1, errno, "open %s failed", argv[2]);
    }

    // 1. 获取文件的大小
    struct stat sb;
    fstat(src, &sb);
    off_t fsize = sb.st_size;
    // 2. 将dst文件的大小设置和src一样
    ftruncate(dst, fsize);

    // copy file
    off_t offset = 0; //copyed file's size
    while (offset < fsize){
        //确定映射区的大小
        off_t length;
        if (fsize - offset >= MMAP_SIZE){
            length = MMAP_SIZE;
        }else{
            length = fsize - offset;
        }
        //映射
        void* addr1 = mmap(NULL, length, PROT_READ, MAP_SHARED, src, offset);
        if (addr1 == MAP_FAILED){
            error(1, errno, "mmap %s failed", argv[1]);
        }

        void* addr2 = mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED,  dst, offset);
        if (addr2 == MAP_FAILED){
            error(1, errno, "mmap %s failed", argv[2]);
        }

        //操作内存
        memcpy(addr2, addr1, length);

        //解除映射
        munmap(addr1, length);
        munmap(addr2, length);

        offset += length;
    }   // offset = fsize
    
    close(src);
    close(dst);

    return 0;
}

