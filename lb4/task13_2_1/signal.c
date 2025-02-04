#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sched.h>

int main(){
    system(">res.txt");
    int pid[3];
    if ((pid[0] =fork()) == 0)
        execl("son1", "son1", NULL);
    if ((pid[1] = fork()) == 0)
        execl("son2", "son2", NULL);
    if ((pid[2] = fork()) == 0)
        execl("son3", "son3", NULL);

    system("ps -l >> res.txt");
    system("echo \"\n\n\" >> res.txt");
    kill(pid[0], SIGUSR1);
    kill(pid[1], SIGUSR1);
    kill(pid[2], SIGUSR1);
    system("ps -l >> res.txt");

    for (int i =0; i<3; i++)
        wait(NULL);
    return 0;
}
