#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"
#include "kernel/stat.h"

void child_do(int p[2])
{
    int data;
    int read_data;
    int cp[2];
    pipe(cp);
    close(p[1]);//Only when write side closed, read will return 0
    int len;
    len=read(p[0],&data,4);//read data from pipe
    // printf("len=%d\n",len);
    if(len==0){
        // printf("primes done\n");
        exit(0);
    }
    // int pid=getpid();
    // printf("pid=%d\n",pid);
    printf("prime %d\n",data);
    if(fork()==0){
        close(p[0]);
        child_do(cp);
    }else{
        close(cp[0]);
        while(len!=0){
            len=read(p[0],&read_data,4);
            if(read_data%data!=0) write(cp[1],&read_data,4);
        }
        close(p[0]);
        close(cp[1]);
        wait(0);
    }
    exit(0);
}

int
main(int argc, char* argv[]){
    int p[2];
    pipe(p);//init the pipeline
    if(fork()==0){
        child_do(p);
    }else{
        close(p[0]);
        for(int i=2;i<=35;i++){
            write(p[1],&i,4);
        }
        close(p[1]);
        wait(0);
    }
    exit(0);
}