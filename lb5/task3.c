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
    
    sigaddset(&act.sa_mask, SIGINT);
    act.sa_flags = 0;
    sigaction(sig, &act, NULL);
    return act.sa_handler;
}


// обработчик сигнала
void handler1(int sig){
    printf("SIGUSR1 обработчик\n");
    sleep(30);
    printf("SIGUSR1 обработчик завершился после 30 сек\n");
}


int main(){
    //надежный обработчик
    //mysig(SIGUSR1, handler1);
    
    //ненадежный
    signal(SIGUSR1, handler1);

    // ждем поступления сигналов
    for(;;) pause();

    return 0;
}
