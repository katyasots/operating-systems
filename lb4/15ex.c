#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    printf("Начальные приоритеты: %d\n", getpriority(PRIO_PROCESS, 0));
    system("ps -o pid,pri,ni,cmd,cls");

    //делаем процесс менее приоритетным
    nice(5);
    printf("Измененные: %d\n", getpriority(PRIO_PROCESS, 0));
    system("ps -o pid,pri,ni,cmd,cls");

    //попытка сделаеть более приоритетный процесс с отрицательным nice
    // но это невозможно без прав суперпользователя
    nice(-5);
    printf("Измененные: %d\n", getpriority(PRIO_PROCESS, 0));
    system("ps -o pid,pri,ni,cmd,cls");

    //снова меняем приоритет процесса
    nice(9);
    printf("Измененные: %d\n", getpriority(PRIO_PROCESS, 0));
    system("ps -o pid,pri,ni,cmd,cls");

    return 0;
}
