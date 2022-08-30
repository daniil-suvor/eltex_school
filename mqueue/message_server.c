#include "chat_room.h"
#define MAX_CLIENT 20

int main() {
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_LEN_QUEUE;
    attr.mq_msgsize = sizeof(struct message);
    attr.mq_curmsgs = 0;
    mqd_t server;
    if ((server = mq_open(SERVER_NAME, O_RDWR | O_CREAT, QUEUE_PERMISSIONS, &attr)) == -1) {
        fprintf(stderr, "Erorr open server\n");
        exit(0);
    }
    struct client clients[MAX_CLIENT];
    for (int i = 0; i < MAX_CLIENT; i++) {
        clients[i].empty = 1;
    }
    int client_num = 0;
    int empty_i = 0;
    
    while (1) {
        struct message from_client;
        if (mq_receive(server, (char*)&from_client, sizeof(struct message), NULL) == -1) {
            fprintf(stderr, "Erorr receive message\n");
        } else {
            if (from_client.type == 0) {
                for (empty_i = 0; (empty_i < MAX_CLIENT) && (clients[empty_i].empty == 0); empty_i++) {}
                if ((clients[empty_i].id = mq_open(from_client.from, O_RDWR)) == -1) {
                    fprintf(stderr, "Erorr open client %s\n", from_client.from);
                } else {
                    clients[empty_i].empty = 0;
                    strcpy(clients[empty_i].name, from_client.from);
                    printf("add client %s\n", from_client.from);
                    client_num++;
                }
            } else if (from_client.type == 1) {
                for (int i = 0; i < MAX_CLIENT; i++) {
                    if (strcmp(clients[i].name, from_client.from) == 0) {
                        clients[i].empty = 1;
                        mq_close(clients[i].id);
                        client_num--;
                    }
                }
                if (client_num == 0)
                    break;
            } else {
                //printf("%s\n", from_client.mes);
                for (int i = 0; i < MAX_CLIENT; i++) {
                    // if ((clients[i].empty == 0) && (strcmp(clients[i].name, from_client.from) != 0)) {
                    if (clients[i].empty == 0) {
                        if (mq_send(clients[i].id , (char*)&from_client, sizeof(struct message), 0) == -1) {
                            fprintf(stderr, "Erorr send client %d\n", i);
                        }
                    }
                }
            }
        }
    }
    if (mq_close(server) == -1) {
        fprintf(stderr, "Erorr close queue\n");
        exit(0);
    }
    mq_unlink(SERVER_NAME);
    return 0;
}