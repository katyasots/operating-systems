#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
    int pid, ppid, status;
    pid = getpid();
    ppid = getppid();
    printf("FATHER PARAM: pid=%i  ppid=%i\n", pid, ppid);
    if (fork()==0)
        execl("son", "son", NULL);
    system("ps -xf > file.txt");
    wait(&status);
    printf("Child process is finished with status %d\n", status);

    return 0;
}