#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

void (*mysig(int sig, void (*hnd)(int)))(int) {
    // надежная обработка сигналов
    struct sigaction act;
    act.sa_handler = hnd;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGRTMIN);
    sigaddset(&act.sa_mask, SIGRTMAX);
    sigaddset(&act.sa_mask, SIGINT);
    act.sa_flags = 0;
    sigaction(sig, &act, 0);
    return act.sa_handler;
}


// обработчик сигнала
void handler1(int sig){
    printf("SIGUSR1 обработчик\n");
    sleep(30);
    printf("SIGUSR1 обработчик завершился после 30 сек\n");
}

// обработчик сигнала
void handler2(int sig){
    printf("SIGRTMIN обработчик\n");
    sleep(30);
    printf("SIGRTMIN обработчик завершился после 30 сек\n");
}

// обработчик сигнала
void handler3(int sig){
    printf("SIGRTMAX обработчик\n");
    sleep(30);
    printf("SIGRTMAX обработчик завершился после 30 сек\n");
}


int main(){
    mysig(SIGUSR1, handler1);
    mysig(SIGRTMIN, handler2);
    mysig(SIGRTMAX, handler3);
    
    // ждем поступления сигналов
    for(int i=0;i<1;i++) pause();

    return 0;
}
