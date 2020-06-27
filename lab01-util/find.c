/*
    lab-util
    Write a simple version of the UNIX find program: 
    find all the files in a directory tree whose name matches a string. 
    Your solution should be in the file user/find.c.
*/

#include "kernel/types.h"
#include "kernel/fs.h"
#include "kernel/stat.h"
#include "user/user.h"

int match(char *filepath, char *pattern){
    char *p;
    for(p = filepath + strlen(filepath); p >= filepath && *p != '/'; p--);
    p++;

    if(strcmp(p, pattern) == 0){
        return 1;
    }
    return 0;
}

void find(char *path, char *pattern){
    int fd;
    struct stat st;
    struct dirent de;
    char buffer[512];
    char *p;

    if((fd = open(path, 0)) < 0){
        printf("open error: %s\n", path);
        return;
    }
    if(fstat(fd, &st) < 0){
        printf("stat error: %s\n", path);
        return;
    }

    switch(st.type){
        case T_FILE:
            if(match(path, pattern)){
                printf("%s\n", path);
            }
            break;
        
        case T_DIR:
            memmove(buffer, path, strlen(path));
            p = buffer + strlen(path);
            *p++ = '/';
            
            while(read(fd, &de, sizeof(de)) == sizeof(de)){
                if(*(char*)de.name == '.' || strlen(de.name) == 0){
                    continue;
                }
                char *tmp = p;
                memmove(tmp, de.name, DIRSIZ);
                tmp += DIRSIZ;
                *tmp = '\0';
                find(buffer, pattern);    
            }
            break;
    }
    close(fd);

}

int main(int argc, char *argv[]){
    if(argc != 3){
        printf("find usage:\n\t>>> find dir file");
        exit();
    }
    find(argv[1], argv[2]);
    exit();   
}