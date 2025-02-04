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

int main() {
    // направление вывода в текстовый файл
    //freopen("task3.txt", "w", stdout);
    pid_t pid;

    ////////////////////////////////////////
    // изменение процедуры планирования
    struct sched_param param;
    param.sched_priority = 1;
    if (sched_setscheduler(0, SCHED_FIFO, &param) == -1) {
        perror("sched_setscheduler");
        exit(EXIT_FAILURE);
    }
    ///////////////////////////////////////

    for (int i = 0; i < 5; i++) {
        pid = fork();
        if (pid == 0) {
            // дочерний процесс
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
    for (int i = 0; i < 5; i++) {
        wait(&status);
    }
    return 0;
}
