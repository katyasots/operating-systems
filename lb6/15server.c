#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_BUFFER_SIZE 1024
#define SERVER_PORT 8888

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[MAX_BUFFER_SIZE];

    // Создание сокета
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // Настройка адреса сервера
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // Привязка сокета к адресу
    bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));


    // Прием и отправка сообщений
    while (1) {
        ssize_t bytes_received = recvfrom(sockfd, buffer, MAX_BUFFER_SIZE - 1, 0,
                                          (struct sockaddr*)&client_addr, &addr_len);
        if (bytes_received <= 0) continue;

        buffer[bytes_received] = '\0';
        printf("Полученное сообщение от клиента: %s\n", buffer);

    sendto(sockfd, "Сообщение получено", strlen("Сообщение получено"), 0,
                (struct sockaddr*)&client_addr, addr_len);
    }

    close(sockfd);
    return 0;
}
