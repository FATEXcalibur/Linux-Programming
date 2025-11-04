# 使用场景：将每一个.c文件生成对应的可执行文件

Srcs := $(wildcard *.c)
Outs := $(patsubst %.c, %, $(Srcs))

CC := gcc
CFLAGS = -Wall -g -D_GNU_SOURCE

ALL: $(Outs)

%: %.c
	$(CC) $< -o $@ $(CFLAGS)

.PHONY: clean rebuild ALL

clean:
	$(RM) $(Outs)
rebuild: clean ALL
