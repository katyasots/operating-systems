#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

// переменная для изначального обработчика
struct sigaction old_hand;

// 2ой обработчик сигнала
void handler2(int sig){
    printf("SIGRTMIN во 2ом обработчике\n");

    // восстановление старого обработчика
    sigaction(SIGRTMIN, &old_hand, NULL);
    sleep(10);
    printf("2ой обработчик завершился после 10 сек\n");
}

// 1ый обработчик сигнала
void handler1(int sig){
    printf("SIGRTMIN во 1ом обработчике\n");

    // надежная обработка сигналов
    struct sigaction sa;
    sa.sa_handler = handler2;
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGINT);

    // установка втрого обработчика
    sigaction(SIGRTMIN, &sa, &old_hand);
    sleep(10);
    printf("1ый обработчик завершился после 10 сек\n");
}

int main(){
    // надежная обработка сигналов
    struct sigaction act;
    act.sa_handler = handler1;
    // пустая маска
    sigemptyset(&act.sa_mask);

    // добавление маски в сигнал, блокирующийся во время обработки других
    sigaddset(&act.sa_mask, SIGINT);

    // установка первого обработчика для SIGRTMIN
    sigaction(SIGRTMIN, &act, NULL);

    // ждем поступления сигналов
    for(;;) pause();

    return 0;
}
