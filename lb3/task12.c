#include <stdio.h>
#include <sched.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>


void itoa(char *buf, int value) {
    sprintf(buf, "%d", value);
}


int main() {
    int status;
    int fdrd, fdwr;
    char str1[10], str2[10];
    struct sched_param param;
    param.sched_priority = 1;
    sched_setscheduler(0, SCHED_RR, &param);

    // Заблокировать все страницы памяти процесса в оперативной памяти
    if (mlockall(MCL_CURRENT | MCL_FUTURE) < 0)
        perror("mlockall error");


    // Открыть файл для чтения и файла для записи
    if ((fdrd = open("task12_input.txt", O_RDONLY)) == -1)
        perror("Opening file");
    if ((fdwr = creat("task12_output.txt", 0666)) == -1)
        perror("Creating file");
    // Преобразовать дескрипторы файлов в строковые значения

    itoa(str1, fdrd);
    itoa(str2,fdwr);
    // Создать два процесса-потомка
    for (int i = 0; i < 2; i++) {
        if (fork() == 0) {
            param.sched_priority = 90;
            sched_setscheduler(0, SCHED_RR, &param);
            execl("12son.out", "son12", str1, str2, NULL);
        }
    }
        // Ждем завершения детей
    for (int i = 0; i < 2; i++)
        printf("Process pid = %d completed\n", wait(&status));
    // Закрыть файл для чтения
    if (close(fdrd) != 0)
        perror("Closing file");
    
    return 0;
}