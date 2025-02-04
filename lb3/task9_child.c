#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv){
    printf("%s pid=%d, ppid=%d\n", argv[0], getpid(), getppid());
    return (int)argv[0][5] - '0';
}