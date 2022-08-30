#ifndef _CHAT_ROOM_H_
#define _CHAT_ROOM_H_

#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_MES_LEN 256
#define MAX_LEN_QUEUE 10
#define QUEUE_PERMISSIONS 0660
#define MAX_NAME_LEN 20
#define SERVER_NAME "/server-mes"

struct message {
    int type;
    char from[MAX_NAME_LEN +1];
    char mes[MAX_MES_LEN + 1];
};
struct client {
    char name[MAX_NAME_LEN + 2];
    mqd_t id;
    int empty;
};

#endif  // _CHAT_ROOM_H_