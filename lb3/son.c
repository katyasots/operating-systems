#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
    int pid, ppid;
    pid = getpid();
    ppid = getppid();
    printf("SON PARAMS: pid=%i  ppid=%i\n", pid, ppid);
    sleep(5);
    //exit(1); статус завершения 256
    return 0; // статус завершения 0
}