#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"

int main(int argc, char * argv[])
{
    int p[2];
    char message[10];
    int pid;
    pipe(p);
    if(fork()==0){
        // child process
        read(p[0],message,4);//read 4 bytes from pipe
        pid=getpid();
        printf("%d: received %s\n", pid,message);
        close(p[0]);
        write(p[1],"pong",4);
        close(p[1]);
    }else {
        // parent's process
        write(p[1],"ping",4);//write ping to pipe;
        close(p[1]);
        wait(0);
        read(p[0],message,4);
        pid=getpid();
        printf("%d: received %s\n", pid, message);
    }
    exit(0);
}