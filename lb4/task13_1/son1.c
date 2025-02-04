#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <string.h>



void main(){
    int pid, ppid;
    pid = getpid();
    ppid = getppid();

    printf("SON_1 PARAMS: pid=%i, ppid=%i\nFather creates and waits \n", pid, ppid);

    sleep(3);
}