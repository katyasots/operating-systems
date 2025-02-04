#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>

typedef struct
{
    long type;
    char buf[64];
} Message;


int main(int argc, char **argv)
{
    // id очереди по ее ключу
    int qid = msgget((key_t)atoi(argv[1]), IPC_CREAT | 0666);

    // отправка сообщений в ящик
    // Message msg1 = {1, "first message"};
    // Message msg2 = {2, "second message"};
    // msgsnd(qid, &msg1, strlen(msg1.buf) + 1, 0);
    // msgsnd(qid, &msg2, strlen(msg2.buf) + 1, 0);

    // получение сообщений из очереди
    // Message rmsg1;
    // Message rmsg2;
    // msgrcv(qid, &rmsg1, 64, 1, 0);
    // msgrcv(qid, &rmsg2, 64, 2, 0);
    // printf("message with type %ld recieved: %s\n", rmsg1.type, rmsg1.buf);
    // printf("message with type %ld recieved: %s\n", rmsg2.type, rmsg2.buf);

    // удаление очереди
    msgctl(qid, IPC_RMID, 0);
    return 0;
}
