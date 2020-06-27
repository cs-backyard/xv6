/*
    labb-util
    Your goal is to use pipe and fork to set up the pipeline. 
    The first process feeds the numbers 2 through 35 into the pipeline. 
    For each prime number, you will arrange to create one process that reads from 
    its left neighbor over a pipe and writes to its right neighbor over another pipe. 
    Since xv6 has limited number of file descriptors and processes, the first process can stop at 35.
*/

#include "kernel/types.h"
#include "user/user.h"

int prime(int n){
    for(int i = 2; i < n; i++){
        if(n % i == 0){
            return 0;
        }
    }
    return 1;
}


int main(int argc, char *argv[]){
    for(int i = 2; i <= 35; i++){
        if(!prime(i)){
            continue;
        }
        int pipefd[2];
        pipe(pipefd);
        if(fork() == 0){
            close(pipefd[1]);
            int p;
            if(read(pipefd[0], &p, 1) > 0){
                printf("prime %d\n", p);
            }
            close(pipefd[0]);
            exit();
        }
        close(pipefd[0]);
        write(pipefd[1], &i, 1);
        wait();
        close(pipefd[1]);
    }
    exit();
}