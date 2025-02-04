#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>


// обработчик сигнала
void handler1(int sig, siginfo_t *info, void *context){
    if (sig == SIGRTMIN){
        printf("SIGRTMIN: %d\n", info->si_value.sival_int);

        //вложенная отправка
        if(info->si_value.sival_int == 0){
            union sigval val;
            val.sival_int = 3;
            sigqueue(getpid(), SIGRTMIN, val);            
        }
        sleep(1);
    }
    else if(sig == SIGRTMIN+1){
        printf("SIGRTMIN+1: %d\n", info->si_value.sival_int);
        sleep(1);
    }
    else if(sig == SIGRTMIN+2){
        printf("SIGRTMIN+2: %d\n", info->si_value.sival_int);
        sleep(1);
    }
    else if(sig == SIGUSR1){
        printf("SIGUSR1: %d\n", info->si_value.sival_int);
        sleep(1);
    }
    else if(sig == SIGUSR2){
        printf("SIGUSR2: %d\n", info->si_value.sival_int);
        sleep(1);
    }
}

// обработчик сигнала
void handler2(int sig, siginfo_t *info, void *context){
    union sigval val;
    for(int i = 0; i<3; ++i){
        val.sival_int = i;
        sigqueue(getpid(), SIGRTMIN, val);
    }
    for(int i = 0; i<3; ++i){
        val.sival_int = i;
        sigqueue(getpid(), SIGRTMIN+1, val);
    }
    for(int i = 0; i<3; ++i){
        val.sival_int = i;
        sigqueue(getpid(), SIGRTMIN+2, val);
    }
    for(int i = 0; i<3; ++i){
        val.sival_int = i;
        sigqueue(getpid(), SIGUSR1, val);
    }
    for(int i = 0; i<3; ++i){
        val.sival_int = i;
        sigqueue(getpid(), SIGUSR2, val);
    }
    sleep(2);
}

int main(){
    // сигналы обрабатываются как сигналы реального времени
    struct sigaction sa;
    sa.sa_sigaction = handler1;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    sigaddset(&sa.sa_mask, SIGRTMIN);
    sigaddset(&sa.sa_mask, SIGRTMIN+1);
    sigaddset(&sa.sa_mask, SIGRTMIN+2);
    sigaddset(&sa.sa_mask, SIGUSR1);
    sigaddset(&sa.sa_mask, SIGUSR2);
    
    sigaction(SIGRTMIN, &sa, NULL);
    sigaction(SIGRTMIN+1, &sa, NULL);
    sigaction(SIGRTMIN+2, &sa, NULL);
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    //сигнал, который создаст очередь
    struct sigaction act;
    act.sa_sigaction = handler2;
    sigemptyset(&act.sa_mask);

    sigaddset(&act.sa_mask, SIGRTMIN);
    sigaddset(&act.sa_mask, SIGRTMIN+1);
    sigaddset(&act.sa_mask, SIGRTMIN+2);
    sigaddset(&act.sa_mask, SIGUSR1);
    sigaddset(&act.sa_mask, SIGUSR2);

    act.sa_flags = SA_SIGINFO;
    
    sigaction(SIGFPE, &act, NULL);
    union sigval val;
    sigqueue(getpid(), SIGFPE, val);
    
    // ждем поступления сигналов
    for(;;) pause();

    return 0;
}
