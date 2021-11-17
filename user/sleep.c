#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int 
main(int argc, char* argv[])
{
    if(argc < 2){
        fprintf(2, "Usage: sleep clocks\n");
        exit(1);
    }
    int clocks= atoi(argv[1]);
    // if (clocks < 0){
    //     fprintf(2, "Usage: clocks should >0\n");
    //     exit(1);
    // }
    // It is seems that atoi will always be positive, after read ./ulib.c
    sleep(clocks);

    exit(0);
}