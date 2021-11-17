#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int
main(int argc, char* argv[]){
    char buf[512];
    char* args[MAXARG];
    if(argc<2){
        fprintf(2,"Usage xargs...\n");
        exit(1);
    }
    if(argc+1>MAXARG){
        fprintf(2,"Too many args\n");
        exit(1);
    }

    int i;
    for(i=1;i<argc;i++) args[i-1]=argv[i];

    args[argc]=0;
    int len;
    while(1){
        i=0;
        while(1){
            len=read(0,&buf[i],1);
            if (len==0||buf[i]=='\n') break;
            i++;
        }
        if(i==0) break;

        buf[i]=0;
        args[argc-1]=buf;
        if(fork()==0){
            exec(args[0],args);
            exit(0);
        }else{
            wait(0);
        }
    }


    exit(0);
}