/* Assignment 3 
 * kbint.c
 * by Xiang Zhi Tan
 * 906 908 1090
 * CS 354 Fall 2013 - Section 2
 *
 * This program calls an alarm for the interval
 * specified by the user untill a cap also specificed
 * by the user.
 * changes mode when the user interrupts with the 
 * press of ctrl-c. and output the string written by
 * the user
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <ctype.h>
#include <string.h>
#define BUFFERSIZE 60 

/*the time interval for alarm*/
int interval;
/*specify the mode it is in*/
volatile int mode;

/*
 *Changes the mode of the program
 * argv: the signal num
 */
void ctrlhandler(int argv);

/*
 *Function called when the signal 
 * SIGALRM is called
 *  argv: the signal num
 */
void signal_handler(int argv);


int main(int argc, char *argv[])
{
    /*value to check*/
    int check;
    /*store the start time*/
    time_t starttime;
    /*checking value to check if time works*/
    time_t checktime;
    /*when the program should end*/
    int endtime;
    /*use to store the current time*/
    time_t currtime;
    /*the maximum time*/
    int cap;
    /*store the string given by user*/
    char* string;
    /*store the size of the string*/
    int size;
    /*counter value*/
    int i;
    /*local mode*/
    int localmode;
    /*sigaction for the signal SIGALRM*/
    struct sigaction action;
    /*sigaction for the signal SIGINT*/
    struct sigaction ctrlaction;

    /*check if the argument given by the user is valid*/
    if (argc != 4) {
    fprintf(stderr, "usage: alarm <interval> <cap> <string>\n");
    exit(1);
    }

    /*set the local and global mode*/
    mode = 0;
    localmode = 0;

    /*convert the time in arguments into integer*/
    interval = atoi(argv[1]);
    cap = atoi(argv[2]);

    /*check if the time are valid*/
    if(interval <= 0 || cap <= 0)
    {
        fprintf(stderr, "enter valid interval and cap\n");
        exit(1);
    }
    /*check if the interval is long than the cap*/
    if(interval > cap)
    {
        fprintf(stderr, "enter interval that is shorter than cap\n");
        exit(1);
    }

    /*get the current time*/
    checktime = time(&starttime);
    /*check if the time function get the time correctly*/
    if(checktime != starttime)
    {
        fprintf(stderr, "function time failed\n");
        exit(1);
    }

    /*calculate when the program should end*/
    endtime = starttime + cap;

    /*check if 4th argument is NULL, will not happen */
    if(argv[3] == NULL)
    {
        fprintf(stderr, "usage: alarm <interval> <cap> <string>\n");
        exit(1);
    }

    /*get the length of the string give by user.
    would always be more than 0 because we check if its empty*/
    size = strlen(argv[3]);
    /*calculate the total size of the string*/
    size = (sizeof(char) * size + 1);
    /*check if size is valid*/
    if( size <= 0 )
    {
        fprintf(stderr, "size of string proved is unvalid\n");
        exit(1);
    }
    string = malloc(size);
    /*check if malloc function correctly*/
    if( string == NULL )
    {
        fprintf(stderr, "malloc failed, not enough memory\n");
        exit(1);        
    }
    /*copy the string to a local string*/
    string = strncpy(string,argv[3],size);

    /*assign the handler for the signal SIGALRM*/
    action.sa_handler = signal_handler;
    check = sigaction(SIGALRM, &action, NULL);
    /*check if sigaction function correctly*/
    if( check != 0 )
    {
        fprintf(stderr, "sigaction failed\n");
        exit(1);        
    }

    /*assign the handler for the signal SIGINT*/
    ctrlaction.sa_handler = ctrlhandler;
    check = sigaction (SIGINT, &ctrlaction, NULL);
    /*check if sigaction function correctly*/
    if( check != 0 )
    {
        fprintf(stderr, "sigaction failed\n");
        exit(1);        
    }


    /*start the first alarm*/
    alarm(interval);
    /*loop until the current time is larger than end time*/
    while(1)
    {
        /*get current time*/
        checktime = time(&currtime);
        /*check if the time function get the time correctly*/
        if(checktime != currtime)
        {
            fprintf(stderr, "function time failed\n");
            exit(1);
        }
        /*check if current time is larger */
        if(currtime > endtime)
        {
            /*break the loop*/
            break;
        }
        /*check if there was a mode change*/
        if(mode != localmode)
        {
            /*this mean all change to uppercase*/
            if(mode == 1)
            {
                for(i = 0 ; i < strlen(string) ; i++)
                {
                    check = string[i];
                    /*we do not need to check for toupper because
                     if it is not able to convert it will return the
                     original value, since we know string[i] is valid
                     this should not be a problem*/
                    string[i] = toupper(string[i]);
                }
            }
            /*this mean all change to lower case*/
            else{
                for(i = 0 ; i < strlen(string) ; i++)
                {
                    check = string[i];
                    /*we do not need to check for tolower because
                     if it is not able to convert it will return the
                     original value, since we know string[i] is valid
                     this should not be a problem*/
                    string[i] = tolower(string[i]);

                }
            }
            /*print string*/
            printf("%s\n",string);
            /*change local mode*/
            localmode = mode;
        }
    }
    /*exit program*/
    return 0;
}

void signal_handler(int argv)
{
    /*to store the time*/
    time_t timer;
    /*to check the time*/
    time_t checktime;
    /*buffer for function strftime*/
    char buffer[BUFFERSIZE];
    /*to store the time info*/
    struct tm* tm_info;
    /*check value*/
    int check;

    /*get the current time*/
    checktime = time(&timer);
    /*check if the time function get the time correctly*/
    if(checktime != timer)
    {
        fprintf(stderr, "function time failed\n");
        exit(1);
    }

    /*convert the time to a specific format*/
    tm_info = localtime(&timer);
    /*check if localtime doesn't work correctly*/
    if(tm_info == NULL)
    {
        fprintf(stderr, "function localtime failed");
        exit(1);
    }

    /*format the output string*/
    check = strftime(buffer, BUFFERSIZE,
        "current time is %a %b %d %H:%M:%S %Y", tm_info);
    /*check if strftime worked correctly*/
    if(check == 0)
    {
        fprintf(stderr, "time formating failed\n");
        exit(1);
    }
    
    /*output the string*/
    printf("%s\n",buffer);
    /*set the next alarm*/
    check = alarm(interval);
    /*check alarm function,it is 0 because no alarm
    is set since last alarm called this function*/
    if(check != 0)
    {
        fprintf(stderr, "alarm set error\n");
        exit(1);        
    }
}

void ctrlhandler(int argv)
{
    /*alternate the number mode between 0 and 1*/
    if(mode != 0)
    {
        mode = 0;
        return;
    }
    else{
        mode = 1;
        return;
    }
}