#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>


void work() {
    int n = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 1000000000; j++) 
            n += 1;
        printf("pid=%d, ppid=%d, policy=", getpid(), getppid());
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

    }
}

int main()
{
    // Изменение политики планирования
    struct sched_param param;
    param.sched_priority = 1;
    if (sched_setscheduler(0, SCHED_RR, &param) == -1) {
        perror("sched_setscheduler");
        exit(EXIT_FAILURE);
    }

    // для сына создается потомок, т е внук родительского
    if (!fork()) {
        param.sched_priority = 99;
        sched_setscheduler(0, SCHED_RR, &param);
        if (!fork()) {
            param.sched_priority = 99;
            sched_setscheduler(0, SCHED_RR, &param);
        } else {
            sched_yield();
        }
    }
    sched_getparam(0, &param);
    printf("START: pid=%d, ppid=%d, priority=%d, policy=", getpid(), getppid(), param.sched_priority);
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
    // запускается трудоемкая задача
    work();
    printf("END: pid=%d, ppid=%d, policy=", getpid(), getppid());
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
    // родители дожидаются детей
    wait(NULL);
    return 0;
}
