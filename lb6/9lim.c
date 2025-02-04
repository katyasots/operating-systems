#include <unistd.h>
#include <stdio.h>
#include <limits.h>

int main() {
    printf("PIPE_BUF: %d\n", PIPE_BUF);
    long open_max = sysconf(_SC_OPEN_MAX);
    printf("OPEN_MAX: %ld\n", open_max);
    return 0;
}
