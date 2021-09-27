#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char* agrv[]){
    int temp;
    if(argc<2){
        fprintf(2,"Usage sleep...\n");
        exit(1);
    }

    temp=atoi(agrv[1]);
    sleep(temp);
    exit(0);
}