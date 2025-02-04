#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
 

int main(int argc, char** argv){
    // открытие канала для чтения, где записано имя канала для записи
    int chan1 = open("channel_write", O_RDONLY);
    if(chan1 == -1){
        printf("Can't open channel for reading\n");
        exit(0);
    }
    // открытие канала для записи
    int chan2 = open("channel_read", O_WRONLY);
    if(chan2 == -1){
        printf("Can't open channel for reading\n");
        exit(0);
    }
    
    // чтение имени файла из первого канала
    char fileName[100];
    bzero(fileName, 100);
    int res = read(chan1, fileName, 100);
    if(res <= 0){
        printf("Can't read filename from channel1\n");
        exit(0);
    }

    // открытие файла на чтение
    FILE *f = fopen(fileName, "r");
    if(!f){
        printf("Can't open file %s\n", fileName);
        exit(0);
    }
    char buf[100];
    while(!feof(f)){
        // чтение данных из файла
        int res = fread(buf, sizeof(char), 100, f);
        // запись их в канал
        write(chan2, buf, res);
    }
    fclose(f);
    // закрытие каналов
    close(chan1);
    close(chan2);
    return 0;
}