#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "shm.h"

int *buf;

int main()
{
    // присоединились к разделяемой памяти и семафорам
    int shmid = shmget(KEY, (BUF_SIZE+1)*sizeof(int), 0666);
    buf = (int*)shmat(shmid, 0, 0);
    int semaphore = semget(KEY, 3, 0666);
    puts("Нажать кнопку для начала работы");
    getchar();
    int val = 0;
    for (int i = 0; i < 10; ++i) {
        // ждем свободных ячеек
        semop(semaphore, wait_not_full, 1);
        // ждем доступа к разделяемой памяти
        semop(semaphore, mem_lock, 1);
        // пишем в ячейку
        ++buf[BUF_SIZE];
        printf("Пишем %d в ячейку %d\n", val, buf[BUF_SIZE]);
        buf[buf[BUF_SIZE]] = val++;
        // освобождаем доступ к памяти
        semop(semaphore, mem_unlock, 1);
        // увеличиваем счетчик занятых ячеек
        semop(semaphore, release_full, 1);
    }
    shmdt(buf);
    return 0;
}
