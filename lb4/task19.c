#include <signal.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/syscall.h>

//тип pthread_t используется для хранения идентификаторов нитей выполнения
pthread_t t1, t2;

void* thread1(void*){
    printf("Thread_1 start\n");
    system("ps -ft >> th1_19.txt");
        //фиксируем время начала
    time_t start = time(NULL);
    int n = 0;
    for(int i = 0; i<5; i++){
        //увеличиваем счетчик и фиксируем время работы
        time_t end = time(NULL);
        printf("th1 num %d, time=%ld\n", ++n, end-start);
        sleep(5);

        //убийство нити по ее tid
        kill(syscall(SYS_gettid), SIGINT);
    }
    printf("Thread_1 finish\n");
}

void* thread2(void*){
    printf("Thread_2 start\n");
    system("ps -ft >> th2_19.txt");
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
    system(">th1_19.txt");
    system(">th2_19.txt");
    
    system("ps -ft > 19res.txt");
    //запускаем две нити, их tid записываем в t1 b t2
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    //ждем выполнения нитей
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    system("ps -ft >> 19res.txt");
    return 0;
}
