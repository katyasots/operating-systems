#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <string.h>


void main(){
    int pid = getpid();
    int ppid = getppid();

    printf("SON_3 PARAMS: pid=%i, ppid=%i\nson3 terminated - ZOMBIE\n", pid, ppid);
    ppid = getppid();

    printf("SON_3 PARAMS: pid=%i, ppid=%i\n", pid, ppid);
}