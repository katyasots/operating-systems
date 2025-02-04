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
#define SERVER_IP "172.20.10.2"

int readFix(int sock, char *buf, int size, int flags)
{
    unsigned msg_len = 0;
    int res = recv(sock, &msg_len, sizeof(unsigned), flags | MSG_WAITALL);
    if (res <= 0)
        return res;
    return recv(sock, buf, msg_len, flags | MSG_WAITALL);
}

int sendFix(int sock, char *buf, int flags)
{
    unsigned msg_len = strlen(buf);
    int res = send(sock, &msg_len, sizeof(unsigned), flags);
    if (res <= 0)
        return res;
    return send(sock, buf, msg_len, flags);
}

int main()
{
    // создаем сокет и подключаемся к серверу
    struct sockaddr_in peer;
    peer.sin_family = AF_INET;
    peer.sin_port = htons(SERVER_PORT);
    peer.sin_addr.s_addr = inet_addr(SERVER_IP);
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    connect(sock, (struct sockaddr*)&peer, sizeof(peer));


    char buf[100];
    while (1) {
        printf("Сообщение для отправки на сервер:\n");
        bzero(buf,100);
        fgets(buf, 100, stdin);
        buf[strlen(buf)-1] = '\0';
        if(strlen(buf) == 0) {
            puts("Завершение работы клиента");
            return 0;
        }
        int res = sendFix(sock, buf,0);
        if (res <= 0) {
            perror("Проблемы при отправке");
            exit(1);
        }
        bzero(buf, 100);
        res = readFix(sock, buf, 100, 0);
        printf("Ответ сервера: %s\n",buf);
    }
}
