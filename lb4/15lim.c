#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(){
    for(int i=-100; i<1; i++){
        setpriority(PRIO_PROCESS, 0, i);
        int pr = getpriority(PRIO_PROCESS, 0);
        if (pr != i)
            continue;
        else{
            printf("Нижняя граница = %d\n", pr);
            break;
        }
    }
    for(int i=1; i<100; i++){
        setpriority(PRIO_PROCESS, 0, i);
        int pr = getpriority(PRIO_PROCESS, 0);
        if(pr == i)
            continue;
        else{
            printf("Верхняя граница = %d\n", pr);
            break;
        }
    }
    return 0;
}