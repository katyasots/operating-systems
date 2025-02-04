#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("/home/katya/os/lb2/task10.txt", "r");
    if (file == NULL) {
        printf("Cannot open file\n");
        return 1;
    }
    char ch;
    while ((ch = fgetc(file)) != EOF)
        putchar(ch);
    fclose(file);
    return 0;
}

