#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_BUFFER_SIZE 1024
#define SERVER_PORT 8888
#define SERVER_IP "127.0.0.1"

int main(int argc, char *argv[]) {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[MAX_BUFFER_SIZE];
    int num_messages = 10; // Количество сообщений для отправки

    // Создание сокета
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    // Настройка адреса сервера
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Отправка сообщений
    for (int i = 1; i <= num_messages; i++) {
        sprintf(buffer, "Сообщение %d", i);
        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
    }

    // Прием ответов
    socklen_t addr_len = sizeof(server_addr);
    for (int i = 1; i <= num_messages; i++) {
        ssize_t bytes_received = recvfrom(sockfd, buffer, MAX_BUFFER_SIZE - 1, 0,
                                          (struct sockaddr*)&server_addr, &addr_len);
        if (bytes_received > 0) {
            buffer[bytes_received] = '\0';
            printf("Ответ сервера: %s\n", buffer);
        } else {
            printf("Нет ответа %d\n", i);
        }
    }

    close(sockfd);

    return 0;
}
