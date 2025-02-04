#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


void handler(int signum){
    //принимаем сигнал, запоминаем время, выводим в файл
    char temp_str[100];
    sprintf(temp_str, "echo \"GET ACTIVE %ld\n\" >> res.txt", time(NULL));
    system(temp_str);
    exit(EXIT_SUCCESS);
}

int main(){
    //собственный разработчик
    signal(SIGUSR1, handler);
    for(int i =0; i < 10000000000; i++){}
    return 0;
}