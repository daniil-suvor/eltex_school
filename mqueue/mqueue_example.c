#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define QUEUE_NAME_CHILD "/child-queue"
#define QUEUE_NAME_PERENT "/perent-queue"
#define MAX_MES_LEN 256
#define MAX_LEN_QUEUE 10
#define QUEUE_PERMISSIONS 0660

int main() {
    mqd_t perent, child;
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_LEN_QUEUE;
    attr.mq_msgsize = MAX_MES_LEN;
    attr.mq_curmsgs = 0;
    if ((perent = mq_open(QUEUE_NAME_PERENT, O_RDWR | O_CREAT, QUEUE_PERMISSIONS, &attr)) == -1) {
        fprintf(stderr, "Erorr open queue\n");
        exit(0);
    }
    if ((child = mq_open(QUEUE_NAME_CHILD, O_RDWR | O_CREAT, QUEUE_PERMISSIONS, &attr)) == -1) {
        fprintf(stderr, "Erorr open queue\n");
        exit(0);
    }
    pid_t pid = fork();
    if (pid == 0) {
        char message[MAX_MES_LEN - 1] = "Hey from child!\n";
        if (mq_send(child, message, strlen(message) + 1, 0) == -1) {
            fprintf(stderr, "Erorr send message\n");
        }
        char rec_message[MAX_MES_LEN];
        if (mq_receive(perent, rec_message, MAX_MES_LEN, NULL) == -1) {
            fprintf(stderr, "Erorr receive message\n");
        } else {
            printf("Messgae from perent - %s\n", rec_message);
        }
        exit(0);
    } else {
        char message[MAX_MES_LEN - 1] = "Hey from perent!\n";
        if (mq_send(perent, message, strlen(message) + 1, 0) == -1) {
            fprintf(stderr, "Erorr send message\n");
        }
        char rec_message[MAX_MES_LEN];
        if (mq_receive(child, rec_message, MAX_MES_LEN , NULL) == -1) {
            fprintf(stderr, "Erorr receive message\n");
        } else {
            printf("Messgae from perent - %s\n", rec_message);
        }
        wait(0);
    }
    if ((mq_close(perent) == -1) || (mq_close(child) == -1)) {
        fprintf(stderr, "Erorr close queue\n");
        exit(0);
    }
    mq_unlink(QUEUE_NAME_CHILD);
    mq_unlink(QUEUE_NAME_PERENT);
    return 0;
}