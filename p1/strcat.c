/* Assignment1 Program 1
 * strcat.c
 *
 * by Xiang Zhi Tan
 * 906 908 1090
 * CS 354 Fall 2013 - Section 2
 *
 * This program takes an file with number written in ASCII 
 * and output the variables.
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#define MAXSTRINGSIZE 60

int main(int argc, char *argv[])
{
    /*Buffer to store the line from input*/
    char buffer[MAXSTRINGSIZE];
    /*store the line read*/
    char* s;
    /*store the name of input file*/
    char *infile;
    /*file pointer to the input file*/
    FILE* fd;

    /*check if the arguments are valid*/
    if (argc != 2) {
       fprintf(stderr, "usage: strcat <file>\n");
       exit(1);
    }

    infile = argv[1];
    fd = fopen(infile, "r");
    assert(fd != NULL);

    s = fgets(buffer, MAXSTRINGSIZE, fd);
    /*loop as long as the line return is not NULL*/
    while(s != NULL)
    {
        /*output the value to the screen*/
        printf("%s", s);
        s = fgets(buffer, MAXSTRINGSIZE, fd);
    }       

    /*close all used file*/
    fclose(fd);
    return 0;
}

