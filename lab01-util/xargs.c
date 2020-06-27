/*
    lab-util
    Write a simple version of the UNIX xargs program: 
    read lines from standard input and run a command for each line, 
    supplying the line as arguments to the command. 
    Your solution should be in the file user/xargs.c.
*/

#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"


int main(int argc, char *argv[]){
    if(argc < 2){
        printf("xargs usage: xargs cmd [args]\n");
        exit();
    }
    char *nargv[MAXARG];
    int i;
    for(i = 1; i < argc; i++){
        nargv[i-1] = argv[i];
    }
    char buffer[512];
    nargv[i-1] = buffer;

    while(1){
        int index = 0;
        int n = 0;
        while((n = read(0, &buffer[index], 1)) > 0 && buffer[index] != '\n'){
            index++;
        }
        if(n <= 0){
            break;
        }
        buffer[index] = '\0';
        if(fork() == 0){
            exec(nargv[0], nargv);
            exit();
        }
        wait();
    }
    exit();
}