#include <signal.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/syscall.h>


//идентификатор нити
pthread_t t1, t2;

int pid;

void handler(int signum, siginfo_t *info, void *context){
    char tmp[100];
    sprintf(tmp, "echo \"Перехвачен сигнал SIGRTMIN+%d\" >> 23res.txt", info->si_value.sival_int);
    system(tmp);
}


// ОТПРАВКА СИГНАЛОВ РЕАЛ ВРЕМЕНИ С ДОП ДАННЫМИ
void* thread1(void*){
    union sigval value;
    value.sival_int = 0;
    for(int i=0; i<20; i++)
        sigqueue(pid, SIGRTMIN, value);
    while (1){}
}

void* thread2(void*){
    union sigval value;
    value.sival_int = 1;
    for(int i=0; i<20; i++)
        sigqueue(pid, SIGRTMIN+1, value);
    while (1){}
}

int main(){
    system(">res23.txt");
    
    //фиксируем pid, чтобы из нити слать сигналы
    pid = getpid();

    // установка обработчиков для сигналов реального времени
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handler;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGRTMIN, &sa, NULL);
    sigaction(SIGRTMIN+1, &sa, NULL);

    //запускаем нити
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);
    
    while(1){}
    return 0;
}

