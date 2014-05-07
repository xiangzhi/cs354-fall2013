/* Assignment1 Program 1
 * strtoint.c
 *
 * by Xiang Zhi Tan
 * 906 908 1090
 * CS 354 Fall 2013 - Section 2
 *
 * This program takes an file with number written in ASCII
 * and save the variable in binary form
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define MAXSTRINGSIZE 60

int main(int argc, char *argv[])
{
    /*temporary use to store the number of character in each line*/
    char buffer[MAXSTRINGSIZE];
    /*store each line*/
    char *s;
    /*store the name of input file*/
    char *infile;
    /*store the name of output file*/
    char *outfile;
    /*temporary store the value of the number in integer*/
    int value;
    /*filestream of input file*/
    FILE* fd;
    /*number to the output file*/
    int ofd;

    /*check if the user have given correct number of arguments*/
    if (argc != 3) {
       fprintf(stderr, "usage: strrev <infile> <outfile>\n");
       exit(1);
    }

    infile = argv[1];
    outfile = argv[2];

    /*initialize the output and input files*/
    fd = fopen(infile, "r");
    ofd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
    /*check if error occur*/
    assert(fd != NULL);
    assert(ofd > -1);

    /*read the first line of the inputfile*/
    s = fgets(buffer, MAXSTRINGSIZE, fd);
    /*continue loop if s is a valid c-string*/
    while(s != NULL)
    {
        /*check if the c-string value is negative by check for "-" character*/
        if(s[0] == '-')
        {
            /*looping value*/
            int i;
            /*looping value*/
            int j;
            j = 0;
            /*create a new String to temporary store the value*/
            char* newString = (char*) malloc( strlen(s) - 2 *sizeof(char));
            /*Copy only the numbers of the c-string*/
            for(i = 2; i<strlen(s); i++)
            {
                newString[j] = s[i];
                j++;
            }
            /*convert the numbers to integer*/
            value = (atoi(newString)*-1);
        }
        else
        {
            /*convert the numbers to integer*/
            value = atoi(s);
        }
        /*write the integer as binary into output file*/
        int rc = write(ofd, &value, sizeof(int));
        assert(rc == sizeof(int));

        /*get the next line*/
        s = fgets(buffer, MAXSTRINGSIZE, fd);
    }       

    /*Close all open files.*/
    close(ofd);
    fclose(fd);
    return 0;
}