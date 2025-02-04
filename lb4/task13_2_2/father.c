#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sched.h>
#include <time.h>
#include <stdio.h>

int main(){
    system(">res.txt");
    //запуск детей
    int pid[2];
    if ((pid[0] =fork()) == 0)
        execl("passive_son", "passive_son", NULL);
    if ((pid[1] = fork()) == 0)
        execl("active_son", "active_son", NULL);

    //время для инициализации детей
    sleep(1);

    //проверяем в табл, что один процесс спит, а другой автивничает
    system("ps -ft >> res.txt");

    //отправляем сигнал и запоминаем это время
    char temp_str[100];
    sprintf(temp_str, "echo \"SEND PASSIVE %ld\n\" >> res.txt", time(NULL));
    kill(pid[0], SIGUSR1);

    //вывод времени отправки и отправляем сигнал
    system(temp_str);
    sprintf(temp_str, "echo \"SEND ACTIVE %ld\n\" >> res.txt", time(NULL));

    kill(pid[1], SIGUSR1);
    system(temp_str);

    for (int i =0; i<2; i++)
        wait(NULL);
    return 0;
}
