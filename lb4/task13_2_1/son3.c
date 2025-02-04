#include <signal.h>
#include <unistd.h>

void handler(int sig){}

//перехватываниее и обработка сигнала
int main(){
    signal(SIGUSR1, handler);
    sleep(5);
    return 0;
}