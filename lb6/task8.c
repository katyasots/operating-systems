#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <string.h>
#define DEF_F_R "8from.txt" 
#define DEF_F_W "8to.txt" 


int main(int argc, char** argv) { 
    char fileToRead[32]; 
    char fileToWrite[32];
    if(argc < 3 ){ 
        printf("Using default fileNames '%s','%s'\n",DEF_F_R,DEF_F_W);
        strcpy(fileToRead,DEF_F_R);
        strcpy(fileToWrite,DEF_F_W);
    } 
    else{
        strcpy(fileToRead, argv[1]);
        strcpy(fileToWrite, argv[2]);
    }
    int filedes[2];
    if(pipe(filedes) < 0){
        printf("Father: can't create pipe\n");
        exit(1);
    }
    printf("pipe is successfully created\n");

        //процесс-сын
    if(fork() == 0){
        //закрытие дескриптора канала на чтение
        close(filedes[0]);
        
        // открытие файла на чтение
        FILE* f = fopen(fileToRead, "r");
        if(!f){
            printf("Son: can't open file %s\n", fileToRead);
            exit(1);
        }
        char buf[100];
        int res;
        while(!feof(f)){
            // чтение данных из файла
            res = fread(buf, sizeof(char), 100, f);
            // запись прочитанной строки в канал
            write(filedes[1], buf, res); 
        }
        // закрытие файла из канала
        fclose(f);
        close(filedes[1]);
        return 0;
    }

        // процесс-родитель
    //закрыте дескриптора канала на запись
    close(filedes[1]);
    // открытие файла для записи
    FILE *f = fopen(fileToWrite, "w");
    if(!f){
        printf("Father: can't open file %s\n", fileToWrite);
        exit(1);
    }
    char buf[100];
    int res;
    while(1){
        // чтение из канала строки
        bzero(buf, 100);
        res = read(filedes[0], buf, 100);
        if(!res) break;
        printf("Read from pipe: %s\n", buf);
        // запись прочитанной строки в файл
        fwrite(buf, sizeof(char), res, f);
    }
    fclose(f);
    close(filedes[0]);
    return 0;
}
    