#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"

void child_work(int p[2])
{
    close(p[1]);
    int mo;
    int len;
    int cp[2];
    int temp;
    pipe(cp);//pipe that used among child process
    len=read(p[0],&mo,4);
    if(len==0){
        exit(0);
    }
    printf("prime %d\n",mo);
    if(fork()==0){
        // child processes' work
        close(p[0]);
        child_work(cp);
    }else {
        // write numbers to pipe: cp
        close(cp[0]);
        while (len!=0){
            len=read(p[0],&temp,4);
            if(temp%mo!=0) write(cp[1],&temp,4);
        }
        close(cp[1]);
        wait(0);
    }
    exit(0);
}

int 
main(int argc, char * argv[])
{
    int p[2];
    pipe(p);
    if(fork()==0){
        // child processes' work
        child_work(p);
    }else {
        int i;
        close(p[0]);
        for(i=2;i<=35;i++){
            write(p[1],&i,4); // write data into pipe
        }
        close(p[1]);
        wait(0); //wait child processes' work done
    }
    exit(0);
}