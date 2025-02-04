#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define DEF_FILENAME "8from.txt" 

int main(int argc, char **argv){
    char fileName[30];
    if(argc < 2){
        printf("Using default file name '%s'\n", DEF_FILENAME);
        strcpy(fileName, DEF_FILENAME);
    }else{
        strcpy(fileName, argv[1]);
    }

    // cоздание именованныx каналов
    mknod("channel_write", S_IFIFO | 0666, 0);
    mknod("channel_read", S_IFIFO | 0666, 0);

    //открытие первого канала
    int chan1 = open("channel_write", O_WRONLY);
    if(chan1 == -1){
        printf("Can't open channel for writing\n");
        exit(0);
    }
    // открытие второго канала
    int chan2 = open("channel_read", O_RDONLY);
    if(chan2 == -1){
        printf("Can't open channel for reading\n");
        exit(0);
    }

    // запись имени файла в первый канал
    write(chan1, fileName, strlen(fileName));
    // чтение содержимого файла из второго канала
    char buf[100];
    for (;;){
        bzero(buf, 100);
        if(read(chan2, buf, 100) <= 0) break;
        printf("Part of file: %s\n", buf);
    }

    // закрытие каналов
    close(chan1);
    close(chan2);
    unlink("channel_write");
    unlink("channel_read");
    return 0;
}