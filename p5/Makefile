mem: mem.c mem.h
	gcc -c -Wall -m32 -fpic mem.c -O
	gcc -m32 -shared -Wall -o libmem.so mem.o -O

clean:
	rm -rf mem.o libmem.so
