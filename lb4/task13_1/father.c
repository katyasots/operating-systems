#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <string.h>

int main(int argc, char *argv[]){
    int sid, pid, pid1, ppid, status;
    char command[50];

    if(argc < 2)
        return -1;
        
    pid = getpid();
    ppid = getppid();
    sid = getsid(pid);
    //формирование команды для вывода информации о процессе в файл
    sprintf(command, "ps xjf | grep \"STAT\\|%d\" > %s", sid, argv[1]);

    printf("FATHER PARAMS: sid=%i, pid=%i, ppid=%i\n", sid, pid, ppid);

//создание дочерних процессов
    if((pid1=fork()) == 0)
        execl("son1", "son1", NULL);
    if(fork() == 0)
        execl("son2", "son2", argv[1], NULL);
    if(fork() == 0)
        execl("son3", "son3", NULL);
// выполнение команды записи в файл
    system(command);
//ожидание завершения процесса с pid1 без блокировки
    waitpid(pid1, &status, WNOHANG);

    return 0;
}