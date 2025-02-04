#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

extern char **environ;

int main(int argc, char **argv){
    system("ps -ft > 8file.txt");
    for(int i=0; environ[i]; i++)
        puts(environ[i]);
    for(int i=1; argv[i]; i++)
        puts(argv[i]);
    return 0;
}