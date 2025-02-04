#include <signal.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/syscall.h>

//тип pthread_t используется для хранения идентификаторов нитей выполнения
pthread_t t1, t2;

    //завершаем поток при помощи pthread_exit и выводим инфу о потоке
void handler(){
    printf("сигнал принялся tid=%ld\n", syscall(SYS_gettid));
    pthread_exit(NULL);
}

void* thread1(void*){
    printf("Thread_1 start\n");
    system("ps -ft >> th1_21.txt");
        //фиксируем время начала
    time_t start = time(NULL);
    int n = 0;
    for(int i = 0; i<5; i++){
        //увеличиваем счетчик и фиксируем время работы
        time_t end = time(NULL);
        printf("th1 num %d, time=%ld\n", ++n, end-start);
        sleep(5);

        //убийство второй нити по ее дескриптору на первой итерации
        if(i==0){
            printf("сигнал отправился из tid=%ld\n", syscall(SYS_gettid));
            pthread_kill(t2, SIGUSR1);
        }
    }
    printf("Thread_1 finish\n");
}

void* thread2(void*){
    printf("Thread_2 start\n");
    system("ps -ft >> th2_21.txt");
        //фиксируем время начала
    time_t start = time(NULL);
    int n = 0;
    for(int i = 0; i<10; i++){
        //увеличиваем счетчик и фиксируем время работы
        time_t end = time(NULL);
        printf("th2 num %d, time=%ld\n", ++n, end-start);
        sleep(1);
    }
    printf("Thread_2 finish\n");
}

int main(){
    system(">th1_21.txt");
    system(">th2_21.txt");
    
    system("ps -ft > 21res.txt");

    //установка обработчика для сигнала
    signal(SIGUSR1, handler);

    //запускаем две нити, их tid записываем в t1 & t2
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);
    sleep(2);

    //ждем выполнения нитей
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    system("ps -ft >> 21res.txt");
    return 0;
}
