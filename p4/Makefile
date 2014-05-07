# MODIFIED BY:  Xiang Zhi Tan, Section 2 
# DATE: November 25, 2013 
# CLASS: CS354 - Fall 2013 - HW4
#

C     = gcc
CFLAGS = -O -Wall -m32
# argument CFLAGS is missing.  Place it here.


# fill in what is needed for target 'all'
all: cachesim.o cache.o trace_file_parser.o
	$(CC) $(CFLAGS) -o cachesim cachesim.o cache.o trace_file_parser.o

cachesim: cachesim.c
			$(CC) -c -o cachesim.o cachesim.c $(CFLAGS)

cache: cache.c
			$(CC) -c -o cache.o cache.c $(CFLAGS)

trace_file_parser:	trace_file_parser.c
			$(CC) -c -o trace_file_parser.o trace_file_parser.c $(CFLAGS)

