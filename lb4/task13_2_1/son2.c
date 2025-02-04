#include <signal.h>
#include <unistd.h>


//реакция игнорирования
int main(){
    signal(SIGUSR1, SIG_IGN);
    sleep(5);
    return 0;
}