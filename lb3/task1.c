#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main(){
    int pid, n;
    n = 1;
    printf("начальное число:%d\n", n);
    pid = fork();
    if(pid==-1){
        perror("fork");
        exit(1);
    }
    if(pid == 0){
        printf("new pid = %d, pprid = %d\n", getpid(), getppid());
        //здесь размещаются вычисления, выполняемые процессом-потомком
        n *= 3;    
    }
    else{
        printf("parrent pid = %d, ppid = %d\n", getpid(), getppid());
        //здесь размещаются вычисления, выполняемые порождающим процессом
        n += 10;
    }
    printf("итоговое число:%d\n", n);
    printf("завершение процесса\n");
    exit(1);
    return 0;
}