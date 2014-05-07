/* Assignment 3 
 * alarm.c
 * by Xiang Zhi Tan
 * 906 908 1090
 * CS 354 Fall 2013 - Section 2
 *
 * This program calls an alarm for the interval
 * specified by the user untill a cap also specificed
 * by the user
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#define BUFFERSIZE 60 

/*the time interval for alarm*/
int interval;

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
    /*sigaction for the signal SIGALRM*/
    struct sigaction action;
    /*use to store the current time*/
    time_t currtime;
    /*the maximum time*/
    int cap;

    /*check if the argument given by the user is valid*/
    if (argc != 3) {
    fprintf(stderr, "usage: alarm <interval> <cap>\n");
    exit(1);
    }

    /*convert the time in arguments into integer*/
    interval = atoi(argv[1]);
    cap = atoi(argv[2]);

    /*check if the time are valid numbers*/
    if(interval <= 0 || cap <= 0)
    {
        fprintf(stderr,"enter valid interval and cap\n");
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
        fprintf(stderr,"function time failed");
        exit(1);
    }

    /*calculate when the program should end*/
    endtime = starttime + cap;

    /*assign the handler for the signal SIGALRM*/
    action.sa_handler = signal_handler;
    check = sigaction (SIGALRM,&action,NULL);
    /*check if sigaction function correctly*/
    if( check != 0 )
    {
        fprintf(stderr,"sigaction failed");
        exit(1);        
    }

    /*start the first alarm*/
    check = alarm(interval);
    /*check if any previous alarm has been set,
    there should never be any alarm set before this*/
    if(check != 0)
    {
        fprintf(stderr,"alarm set error");
        exit(1);        
    }

    /*loop until the current time is larger than end time*/
    while(1)
    {
        /*get current time*/
        checktime = time(&currtime);
        /*check if the time function get the time correctly*/
        if(checktime != currtime)
        {
            fprintf(stderr,"function time failed");
            exit(1);
        }

        /*check if current time is larger */
    	if(currtime > endtime)
        {
            /*break the loop*/
    		break;
    	}
    };
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
        fprintf(stderr,"function time failed");
        exit(1);
    }

    /*convert the time to a specific format*/
    tm_info = localtime(&timer);
    /*check if localtime doesn't work correctly*/
    if(tm_info == NULL)
    {
        fprintf(stderr,"function localtime failed");
        exit(1);
    }

    /*format the output string*/
    check = strftime(buffer, BUFFERSIZE,
        "current time is %a %b %d %H:%M:%S %Y", tm_info);
    /*check if strftime worked correctly*/
    if(check == 0)
    {
        fprintf(stderr,"time formating failed");
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
        fprintf(stderr,"alarm set error");
        exit(1);        
    }
}