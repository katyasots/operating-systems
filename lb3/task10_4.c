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

int main(){
    pid_t pid;
    struct sched_param param;
    for(int i=0; i<4; i++){
        pid = fork();
        if (pid==0){//дочерний процесс
            //чет номер RR, нечет FIFO, приоритет одинаковый
            param.sched_priority = 50;
            if(i%2) 
                sched_setscheduler(0, SCHED_FIFO, &param);
            else sched_setscheduler(0, SCHED_RR, &param);
            printf("START: pid=%d, ppid=%d, policy=", getpid(), getppid());
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
            // трудоемкая задача
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
            exit(EXIT_SUCCESS);
        }
    }
    // Для наблюдения конкуренции дочерних процессов родительский дожидается их выполнения
    int status;
    for (int i = 0; i < 4; i++) {
        wait(&status);
    }
    return 0;
}