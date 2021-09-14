#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int
main(int argc, char* agrv[]){
    int temp=atoi(agrv[1]);
    sleep(temp);
    exit(0);
}