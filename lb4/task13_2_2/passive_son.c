#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


void handler(int signum){
    //принимаем сигнал, запоминаем время, выводим в файл
    char temp_str[100];
    sprintf(temp_str, "echo \"GET PASSIVE %ld\n\" >> res.txt", time(NULL));
    system(temp_str);
    exit(EXIT_SUCCESS);
}

int main(){
    //собственный разработчик
    signal(SIGUSR1, handler);
    sleep(10);
    return 0;
}