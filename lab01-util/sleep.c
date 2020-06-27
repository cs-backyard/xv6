/*
    lab-util
    Implement the UNIX program sleep for xv6; 
    your sleep should pause for a user-specified number of ticks. 
    (A tick is a notion of time defined by the xv6 kernel, namely the time between two interrupts from the timer chip.) 
    Your solution should be in the file user/sleep.c.
*/

#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("sleep error: \n\t you must input one(only) sleep ticks. \n\t for example,  >>> sleep 10 \n");
        exit();
    }

    int n = atoi(argv[1]);
    sleep(n);

    // we must call exit() to 'exit our program'.
    exit();
}