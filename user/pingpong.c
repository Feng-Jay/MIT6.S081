#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"
#include "kernel/stat.h"

int 
main(int argc, char* argv[]){
    int p[2];
    int message;
    int pid;
    pipe(p);//init pipe
    if(fork()==0){
        //child process
        read(p[0],&message,1);
        pid=getpid();
        printf("%d: received ping\n",pid);
        close(p[0]);
        write(p[1],"pong",5);
    }else{
        //parent process
        write(p[1],"1",1);
        close(p[1]);  
        wait(0);
        read(p[0],&message,1);
        pid=getpid();
        printf("%d: received pong\n",pid);
    }
    exit(0);
}