/* Assignment1 Program 1
 * intcat.c
 *
 * by Xiang Zhi Tan
 * 906 908 1090
 * CS 354 Fall 2013 - Section 2
 *
 * This program takes an file with integers written in binary form
 * and output the integer.
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define SIZETOREAD 4


int main(int argc, char *argv[])
{
    /*pointer to input file name*/
    char *infile;
    /*number of input stream*/
    int fd;
    /*counter value for number of byte read by read*/
    int count;
    /*Buffer to store the byte read*/
    int buf;

    /*check if the arguments are correct*/
    if (argc != 2) {
    fprintf(stderr, "usage: intcat <file>\n");
    exit(1);
    }

    infile = argv[1];

    /*open intput file*/
    fd = open(infile, O_RDONLY);
    assert(fd > -1);

    /*read the file according to the sizetoread constant*/
    count = read(fd,&buf,SIZETOREAD);
    /*print the output as long as 4 bytes are read*/
    while(count == SIZETOREAD)
    {
        if( buf < 0)
        {
            buf *=-1;
            printf("- %d\n", buf);
        }
        else
        {
            printf("%d\n",buf);
        }
        /*get the next 4 bytes to read*/
        count = read(fd, &buf, SIZETOREAD);
    }

    /*clos]e all opened file*/
    close(fd);
    return 0;
}

