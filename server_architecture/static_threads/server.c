/************************************************************/
/* This is a stream socket server sample program for INET   */
/* domain sockets. This program listens for a connection    */
/* from a client program, accepts it, reads data from the   */
/* client, then sends data back to connected INET socket.   */
/************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <arpa/inet.h>
#include <pthread.h>
 #include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>

#define DATA "Hello from server"
#define DATA_LEN 256
#define PORT 31415
#define CLIENT_NUM 5
#define MAX_LEN_QUEUE 10
#define QUEUE_PERMISSIONS 0660

struct client {
    mqd_t clients_queue;
    int port;
    pthread_t tid;
};
struct message {
    int client_sock;
    char buf[DATA_LEN];
};
int create_socket(struct sockaddr_in* new_sock, int port, uint32_t ip_adr) {
    int sock;
    int len = sizeof(struct sockaddr_in);

    /***************************************/
    /* Create a INET domain stream socket  */
    /***************************************/
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        printf("SOCKET ERROR\n");
        return -1;
    }

    /***************************************/
    /* change socket options for should    */ 
    /* allow reuse of local addresses.     */
    /***************************************/
    int optval = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1) {
        printf("SETSOCKETOPT ERROR\n");
        return -1;
    }

     /****************************************/
    /* Set up the INET sockaddr structure   */
    /* by using AF_INET for the family      */
    /****************************************/
    new_sock->sin_family = AF_INET;
    new_sock->sin_port = htons(port);
    new_sock->sin_addr.s_addr = htonl(ip_adr);
    if (bind(sock, (struct sockaddr *)new_sock, len) == -1){
        fprintf(stderr, "BIND ERROR\n");
        close(sock);
        return -1;
    }
    return sock;
}
void* work_with_client(void* arg) {
    int client_sock;
    char port[DATA_LEN], buf[DATA_LEN];
    struct client* client = (struct client*)arg;
    int server_sock;
    struct sockaddr_in client_sockaddr;
    struct sockaddr_in server_sockaddr;
    struct message message;
    int len = sizeof(client_sockaddr);
    server_sock = create_socket(&server_sockaddr, client->port, INADDR_LOOPBACK);
    if (server_sock == -1) {
        exit(0);
    }
    if (listen(server_sock, 1) == -1){ 
        fprintf(stderr, "LISTEN ERROR\n");
        close(server_sock);
        exit(1);
    }
    int n = 0;
    while (n < 2) {
        n++;
        if (mq_receive(client->clients_queue, (char*)&message, sizeof(struct message), NULL) != -1) {
            sprintf(port, "%d", client->port);
            if (send(message.client_sock, port, DATA_LEN, 0) == -1) {
                fprintf(stderr, "SEND PORT ERROR\n");
                close(server_sock);
                close(message.client_sock);
                exit(1);
            }
            if ((client_sock = accept(server_sock, (struct sockaddr *) &client_sockaddr, (socklen_t *)&len)) == -1) {
                fprintf(stderr, "ACCEPT ERROR\n");
                close(server_sock);
                close(client_sock);
                exit(1);
            }
            if (recv(client_sock, buf, sizeof(buf), 0) == -1) {
                fprintf(stderr, "RECV ERROR\n");
                close(server_sock);
                close(client_sock);
                exit(1);
            } else {
                printf("DATA RECEIVED = %s\n", buf);
            }
            memset(buf, 0, strlen(buf));
            strcpy(buf, DATA);      
            printf("Sending data...\n");
            if (send(client_sock, buf, strlen(buf), 0) == -1) {
                fprintf(stderr, "SEND ERROR\n");
                close(server_sock);
                close(client_sock);
                exit(1);
            } else {
                printf("Data sent!\n");
            }
            close(message.client_sock);
        } else {
            fprintf(stderr, "ERROR RECV QUEUE\n");
        }
    }
    close(server_sock);
    close(client_sock);
    return NULL;
}

int main(void) {
    int server_sock, client_sock, len;
    len = sizeof(struct sockaddr_in);
    struct sockaddr_in server_sockaddr;
    struct sockaddr_in client_sockaddr;
    struct client clients[CLIENT_NUM];
    char name[20] = "/thread_0";
    struct mq_attr attr;
    for (int i = 0; i < CLIENT_NUM; i++) {
        clients[i].port = PORT + i + 1;
        name[8] = '0' + i;
        attr.mq_flags = 0;
        attr.mq_maxmsg = MAX_LEN_QUEUE;
        attr.mq_msgsize = sizeof(struct message);
        attr.mq_curmsgs = 0;
        if ((clients[i].clients_queue = mq_open(name, O_RDWR | O_CREAT, QUEUE_PERMISSIONS, &attr)) == -1) {
            fprintf(stderr, "Erorr open queue\n");
            exit(0);
        } 
    }
    server_sock = create_socket(&server_sockaddr, PORT, INADDR_LOOPBACK);
    if (server_sock == -1) {
        exit(0);
    }
    if (listen(server_sock, CLIENT_NUM) == -1){ 
        fprintf(stderr, "LISTEN ERROR\n");
        close(server_sock);
        exit(1);
    }
    for (int i = 0; i < CLIENT_NUM; i++) {
        pthread_create(&clients[i].tid, NULL, work_with_client, (void*)&(clients[i]));
    }
    int n = 0;
    int i_queue = 0;
    struct message new_mes[CLIENT_NUM];
    while (n < 8) {
        if ((client_sock = accept(server_sock, (struct sockaddr *) &client_sockaddr, (socklen_t *)&len)) == -1) {
            fprintf(stderr, "ACCEPT ERROR\n");
        } else {
            printf("Client socket ip: %s, port: %d\n", inet_ntoa(client_sockaddr.sin_addr), ntohs(client_sockaddr.sin_port));
            new_mes[i_queue].client_sock = client_sock;
            if (mq_send(clients[i_queue].clients_queue, (char*)&new_mes[i_queue], sizeof(struct message), 0) == -1) {
                fprintf(stderr, "ERROR SEND QUEUE!\n");
                n += 100;
            }
            i_queue++;
            i_queue %= CLIENT_NUM;
            n++;
        }
    }
    for (int i = 0; i < CLIENT_NUM; i++) {
        name[8] = '0' + i;
        mq_close(clients[i].clients_queue);
        mq_unlink(name);
    }
    close(server_sock);
    return 0;
}
