#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
    int pid[3];
    printf("parent pid=%d, ppid=%d\n", getpid(), getppid());

    if(pid[0]=fork() == 0)
        execl("task9_child", "child0", NULL);
    if(pid[1]=fork() == 0)
        execl("task9_child", "child1", NULL);
    if(pid[2]=fork() == 0)
        execl("task9_child", "child2", NULL);
    system("ps -ft > task9.txt");

    for(int i=0; i<3; i++){
        int status;
        int ret_pid = wait(&status);
            printf("pid %d ended, status %d\n", ret_pid, WEXITSTATUS(status));
    }
    return 0;
}