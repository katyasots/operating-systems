#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>

int main(int argc, char **argv){
    int pid = fork();
    char* const vector_args[] = {"task8_1", "first_arg", "sec_arg", NULL};
    char* const env[] = {"ENV_VARIABLE=env_variable", NULL};
    if(pid == 0){
        switch (argv[1][0])
        {
        case '1':
        // замена дочернего процесса программой с аргументами
            execl("task8_1", "task8_1", "first_arg", "sec_arg", NULL);
            break;
        
        case '2':
        // замена дочернего процесса программой с аргументами в виде массива
            execv("task8_1" , vector_args);
            break;

        case '3':
        // возможность использ переменную среду PATH для поиска исполняемого файла
            execlp("echo", "echo", "some_info", NULL);
            break;
        
        case '4':
        // замена дочернего процесса программой, передавая ее окружение в массиве env
            execle("task8_1", "task8_1", "some_info", NULL, env);
            break;
        }
    }
    wait(NULL);
    return 0;
}