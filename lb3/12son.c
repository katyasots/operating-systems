#include <sched.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
    // Заблокировать все страницы памяти процесса в оперативной памяти
    if (mlockall(MCL_CURRENT | MCL_FUTURE) < 0)
        perror("mlockall error");

    char c;
    char buff[3];
    int pid, ppid;
    int fdrd = atoi(argv[1]); // Преобразовать строковый параметр входного файла в целочисленный дескриптор файла
    int fdwr = atoi(argv[2]); // Преобразовать строковый параметр выходного файла в целочисленный дескриптор файла
    pid = getpid(); 
    ppid = getppid();
    printf("son file descriptor = %d\n", fdrd);
    printf("son params: pid=%i ppid=%i\n", pid, ppid);
    system("ps -o uid,gid,ruid,pid,ppid,pgid,tty,vsz,stat,command > 12ps_info.txt");
    // Работа с файлами
    for(;;)
    {
        sleep(2); 
        if (read(fdrd,&c,1) != 1)
            return 0;
        write(fdwr,&c,1);
        printf("pid = %d: %c\n", pid, c);
        if (close(fdrd) != 0)
            perror("Closing file!");
    }
}