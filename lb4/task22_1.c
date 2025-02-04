#include <signal.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/syscall.h>

//кол-во вызовов обработчика
int count = 0;

//идентификатор нити
pthread_t t1;

void handler(){
    count += 1;
    //вывод потока, обрабатывающего сигнал
    printf("сигнал принимается tid=%ld\n", syscall(SYS_gettid));

    //восстанавление обработчика
    if(count == 3)
        // 3 - максимальное кол-во вызовов до восстановления обработчика по умолчанию
        signal(SIGINT, SIG_DFL); 
}

void* thread1(void*){
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigprocmask(SIG_UNBLOCK, &set, NULL);
    signal(SIGINT, handler);
    printf("Thread_1 start tid=%ld\n", syscall(SYS_gettid));
    system("ps -ft >> th1_22.txt");
        //фиксируем время начала
    time_t start = time(NULL);
    int n = 0;
    for(int i = 0; i<4; i++){
        //увеличиваем счетчик и фиксируем время работы
        time_t end = time(NULL);
        printf("th1 num %d, time=%ld\n", ++n, end-start);
        sleep(5);
    }
    printf("Thread_1 finish\n");
}

int main(){
    system(">th1_22.txt");
    
    system("ps -ft > 22res.txt");

    //установка обработчика для сигнала
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigprocmask(SIG_BLOCK, &set, NULL);
    printf("главная нить tid=%ld\n", syscall(SYS_gettid));

    //запускаем нить
    pthread_create(&t1, NULL, thread1, NULL);
    sleep(2);
    system("ps -ft >> 22res.txt");
    //ждем выполнения нити
    pthread_join(t1, NULL);

    system("ps -ft >> 22res.txt");
    return 0;
}

