#include <signal.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/syscall.h>

pthread_t t1, t2, t3, t4;

void work(){
    int n = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 1000000000; j++) 
            n += 1;
        printf("tid=%ld\n", syscall(SYS_gettid));
    }
}

void* thread1(void*) {
    printf("START: tid=%ld\n", syscall(SYS_gettid));
    work();
    printf("END: tid=%ld\n", syscall(SYS_gettid));
}

void* thread2(void*) {
    printf("START: tid=%ld\n", syscall(SYS_gettid));
    work();
    printf("END: tid=%ld\n", syscall(SYS_gettid));
}

void* thread3(void*) {
    printf("START: tid=%ld\n", syscall(SYS_gettid));
    work();
    printf("END: tid=%ld\n", syscall(SYS_gettid));
}

void* thread4(void*) {
    printf("START: tid=%ld\n", syscall(SYS_gettid));
    work();
    printf("END: tid=%ld\n", syscall(SYS_gettid));
}

int main()
{   
    // меняем политику планирования родителя
    // struct sched_param param;
    // param.sched_priority = 1;
    // sched_setscheduler(0, SCHED_RR, &param);
    switch (sched_getscheduler(0))
    {
        case SCHED_FIFO:
            printf("SCHED_FIFO\n");
            break;
        case SCHED_RR:
            printf("SCHED_RR\n");
            break;
        case SCHED_OTHER:
            printf("SCHED_OTHER\n");
            break;
    }
    // запускаем потоки
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);
    pthread_create(&t3, NULL, thread3, NULL);
    pthread_create(&t4, NULL, thread4, NULL);
    system("ps -eLo pid,tid,cls,pri,rtprio,ni,cmd | grep ./task24_1 > 24_1res.txt");
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    return 0;
}