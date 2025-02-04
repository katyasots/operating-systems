#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define SERVER_PORT 8888

int counter = 0;
int flag = 0;

int readFix(int sock, char *buf, int size, int flags)
{
    // чтение фиксированного сообщения, сначала указана длина
    unsigned msg_len = 0;
    int res = recv(sock, &msg_len, sizeof(unsigned), flags | MSG_WAITALL);
    if (res <= 0)
        return res;
    return recv(sock, buf, msg_len, flags | MSG_WAITALL);
}

int sendFix(int sock, char *buf, int flags)
{
    // отправка фиксированного сообщения, сначала указывается длина
    unsigned msg_len = strlen(buf);
    int res = send(sock, &msg_len, sizeof(unsigned), flags);
    if (res <= 0)
        return res;
    return send(sock, buf, msg_len, flags);
}

void* handler(void *args)
{
    // обработчик для отдельного клиента
    counter += 1;
    int sock = *(int*)args;
    char buf[100];
    while (1) {
        bzero(buf, 100);
        int res = readFix(sock, buf, 100, 0);
        if (res <= 0) {
            puts("Пустое сообщение от клиента, поток завершается");
            pthread_exit(NULL);
        }
        printf("Сообщение от клиента %d: %s\n", sock, buf);
        res = sendFix(sock, buf, 0);
        if (res <= 0) {
            perror("Отправка не удалась");
            pthread_exit(NULL);
        }
    }
}

int main()
{
    // создаем  TCP-сокет, слушающий SERVER_PORT
    struct sockaddr_in listener_info;
    listener_info.sin_family = AF_INET;
    listener_info.sin_port = htons(SERVER_PORT);
    listener_info.sin_addr.s_addr = htonl(INADDR_ANY);
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    bind(sock, (struct sockaddr*)&listener_info, sizeof(listener_info));
    listen(sock, 5);

    // обработка подключений
    while (1) {
        int client = accept(sock, NULL, NULL);
        pthread_t tid;
        pthread_create(&tid, NULL, handler, (void*)&client);
    }
    return 0;
}
