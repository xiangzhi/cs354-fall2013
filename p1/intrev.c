/* Assignment1 Program 1
 * intrev.c
 * by Xiang Zhi
 *
 * This program takes an file with number written in binary form
 * and save the output in reverse order in another file.
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
    /* inputfile name*/
    char *infile; 
    /* output file name*/
    char *outfile;
    /* number of input file stream*/
    int fd;
    /* number of the output file stream*/
    int ofd;
    /* number to check if fstat worked correct*/
    int check;
    /* to store the size of the file*/
    int size;
    /* to sotre the info of the file*/
    struct stat info;  
    /*pointer to a new created integer array*/
    int *p; 
    /* counter value to check if read worked correctly
        and check if EOF have reached*/
    int count;
    /*to store the read value*/
    int buf;
    /*counter value*/
    int i;
    /*counter value */
    int j;
    /*value to check if the int is working correctly*/
    int rc;

    /*check if the correct number arguments is used.*/
    if (argc != 3) {
	   fprintf(stderr, "usage: intrev <inputfile> <outputfile>\n");
	   exit(1);
    }

    infile = argv[1];
    outfile = argv[2];

    /*open the input and output files*/
    fd = open(infile, O_RDONLY);
    ofd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);

    /*Check if the file is opened successfully*/
    assert(fd > -1);
    assert(ofd > -1);

    check = fstat(fd, &info);
    assert(check == 0);

    /*save the size of file*/
    size = info.st_size;
    /*Allocation memory to store value*/
    p = malloc(size);

    /*initialize loop values*/
    i = 0;
    j = 0;

    /*read 4 bytes from the file*/
    count = read(fd,&buf,SIZETOREAD);
    /*continous loop if the read successfully read 4 bytes*/
    while(count == SIZETOREAD)
    {
        /*save the value into the file*/
        p[i] = buf;
        i++;
        count = read(fd, &buf, SIZETOREAD);
    }

    /*loop from the back to get the reverse order*/
    for(j = i - 1; j >= 0;j--)
    {
        /*write the values into the output file*/
        rc = write(ofd, &(p[j]), sizeof(int));
        assert(rc == sizeof(int));
    }

    /*close all opened file*/
    close(ofd);
    close(fd);
    return 0;
}

