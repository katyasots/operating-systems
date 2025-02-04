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
    
    //добавление в маску сигнала, который должен быть отложен
    if(sig == SIGUSR1)
        sigaddset(&act.sa_mask, SIGFPE);
    
    act.sa_flags = 0;
    sigaction(sig, &act, NULL);
    return act.sa_handler;
}


// обработчик сигнала
void handler1(int sig){
    printf("SIGUSR1 обработчик\n");
    // отпрвка другого сигнала
    kill(getpid(), SIGFPE);
    // отправка такого же сигнала
    //kill(getpid(), SIGUSR1);
    sleep(20);
    printf("SIGUSR1 обработчик завершился после 20 сек\n");
}

// обработчик сигнала
void handler2(int sig){
    printf("SIGFPE обработчик\n");
    sleep(20);
    printf("SIGFPE обработчик завершился после 20 сек\n");
}


int main(){
    //надежный обработчик
    mysig(SIGUSR1, handler1);
    mysig(SIGFPE, handler2);

    // ждем поступления сигналов
    for(;;) pause();

    return 0;
}
