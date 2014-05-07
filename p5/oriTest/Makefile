C_FILES := $(wildcard *.c)
TARGETS := ${C_FILES:.c=}

all: ${TARGETS}

%: %.c
	gcc $< -o $@ -g -m32 -L.. -lmem -Xlinker -rpath=.

clean:
	rm -rf ${TARGETS} *.o
