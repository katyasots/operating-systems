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
int shmid;
int semaphore;

void handler(int sig)
{
    // удаление сегмента разделяемой памяти и семафора
    shmdt(buf);
    shmctl(shmid, IPC_RMID, 0);
    semctl(semaphore, 0, IPC_RMID);
}

int main()
{
    signal(SIGINT, handler);
    // создаем участок разделяемой памяти
    shmid = shmget(KEY, (BUF_SIZE + 1) * sizeof(int), IPC_CREAT | 0666);
    // получаем адрес выделенной разделяемой памяти
    buf = (int*)shmat(shmid, 0, 0);

    // создаем массив из 3 семафоров
    // 0 - число свободных ячеек
    // 1 - число занятых ячеек
    // 2 - работа с памятью
    semaphore = semget(KEY, 3, IPC_CREAT | 0666);
    // инициализируем память -1 и говорим, что она свободна
    for (int i = 0; i < BUF_SIZE + 1; ++i)
        buf[i] = -1;
    // устанавливаем все ячейки свободными и разблокируем память
    semop(semaphore, set_free, 1);
    semop(semaphore, mem_unlock, 1);
    puts("Нажать кнопку для начала работы");
    getchar();
    for (int i =0; i < 20; ++i) {
        // ждем пока будет хотя бы одна непустая ячейка
        semop(semaphore, wait_not_empty, 1);
        // ждем возможности взаимодействовать с памятью
        semop(semaphore, mem_lock, 1);
        // читаем информацию из памяти
        // требуемые индекс лежит после основного массива
        int res = buf[buf[BUF_SIZE]];
        buf[BUF_SIZE] = buf[BUF_SIZE] - 1;
        printf("Получен %d из ячейки %d\n", res, buf[BUF_SIZE]+1);
        // освобождаем память и увеличиваем число пустых ячеек
        semop(semaphore, mem_unlock, 1);
        semop(semaphore, release_empty, 1);
    }
    kill(getpid(), SIGINT);
    return 0;
}
