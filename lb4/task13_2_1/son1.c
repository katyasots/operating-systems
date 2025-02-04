#include <signal.h>
#include <unistd.h>

//реакция на сигнал по умолчанию
int main(){
    signal(SIGUSR1, SIG_DFL);
    sleep(5);
    return 0;
}