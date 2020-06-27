/*
    lab-util
    Write a program that uses UNIX system calls to ``ping-pong'' a byte between two processes over a pair of pipes, 
    one for each direction. The parent sends by writing a byte to parent_fd[1] and 
    the child receives it by reading from parent_fd[0]. 
    After receiving a byte from parent, the child responds with its own byte by writing to child_fd[1], 
    which the parent then reads. Your solution should be in the file user/pingpong.c.
*/

#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    int pipefd[2];
    pipe(pipefd);

    if(fork() == 0){
        char buffer[2];
        if(read(pipefd[0], buffer, 2) > 0){
            printf("%d: received ping\n", getpid());
        }
        write(pipefd[1], "pp", 2);

        close(pipefd[0]);
        close(pipefd[1]);
        exit();
    }
    char buffer[2];
    write(pipefd[1], "pp", 2);
    wait();
    if(read(pipefd[0], buffer, 2) > 0){
        printf("%d: received pong\n", getpid());
    }
    
    close(pipefd[0]);
    close(pipefd[1]);
    exit();
}