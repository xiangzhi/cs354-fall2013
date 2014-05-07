/* Assignment1 Program 1
 * strrev.c
 * by Xiang Zhi Tan
 * 906 908 1090
 * CS 354 Fall 2013 - Section 2
 *
 * This program takes an file with number written in ASCII
 * and save the output in reverse order in another file.
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#define MAXSTRINGSIZE 60

typedef struct str{
    char* string;
    struct str* next;
}Str;

/*
 * Push a C-String onto the stack defined at the head.
 * Parameters:
 *  head: pointer to the first variable in the stack
 *  var: the string going to add to the stack
 * Return: the new pointer to the first variable in the stack
 */
Str* push(Str* head,char* var);

/*
 * Pop the first C-String on the stack
 * Parameters:
 *  ptrHead: pointer to a pointer to the first variable in the stack
 * Return: the C-String that was pop out of the stack.
 */
char* pop(Str** ptrHead);

int main(int argc, char *argv[])
{
    /*buffer to store the input file*/
    char buffer[MAXSTRINGSIZE];
    /*store the line of file*/
    char* s;
    /*store the name of input file*/
    char *infile;
    /*store the name of output file*/
    char *outfile;
    /*The head pointer to the stack*/
    Str* head;
    /*Check if fputs is working correctly*/
    int check;
    /*file to the input file*/
    FILE* fd;
    /*file to the oupt file*/
    FILE* ofd;

    /*check if the number of arguments are valid*/
    if (argc != 3) {
       fprintf(stderr, "usage: strrev <inputfile> <outputfile>\n");
       exit(1);
    }

    /*initialize head pointer*/
    head = NULL;

    infile = argv[1];
    outfile = argv[2];

    /*Open input and output files*/
    fd = fopen(infile, "r");
    ofd = fopen(outfile, "w");
    /*check if fopen was successful*/
    assert(fd != NULL);
    assert(ofd != NULL);

    /*read the file one line at a time*/
    s = fgets(buffer, MAXSTRINGSIZE, fd);
    while(s != NULL)
    {
        /*push the line onto the stack*/
        head = push(head, s);
        s = fgets(buffer, MAXSTRINGSIZE, fd);
    }       

    s = pop(&head);
    /*pop stack as long as its not empty(becomes NULL)*/
    while(s != NULL)
    {
        /*write value to outputfile*/
        check = fputs(s, ofd);
        assert(check > -1);
        s = pop(&head);
    }

    /*close all open file*/
    fclose(ofd);
    fclose(fd);
    return 0;
}

Str* push(Str* head, char* var)
{
    /*store the new created Str struct*/
    Str* newStr;
    /*create a new C-string*/
    char* newString;

    newStr = (Str*) malloc(sizeof(Str));
    /*create a new String to store the value to prevent shallow copy*/
    newString = (char*) malloc( strlen(var) *sizeof(char));
    /*copy the string into the new string*/
    strcpy(newString, var);
    /*initialize the value of the new stack*/
    newStr->string = newString;
    newStr->next = head;
    /*return pointer to new head of stack*/
    return newStr;
}
char* pop(Str** ptrHead)
{
    /*To temporary store the C-string to return*/
    char* temp;
    /*to store the pointer to the original stack*/
    Str* tempStr;

    tempStr = *ptrHead;
    /*check if stack is empty*/
    if( (tempStr) == NULL )
    {
        return NULL;
    }
    /*temporary store the pointer to c-string*/
    temp = tempStr->string;
    /*redirect head to the new pointer*/
    (*ptrHead) = tempStr->next;
    /*free up the unuse stack*/
    free(tempStr);
    /*return pointer*/
    return temp;
}