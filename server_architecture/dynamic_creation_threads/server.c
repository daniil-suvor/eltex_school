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


#define DATA "Hello from server"
#define DATA_LEN 256
#define PORT 31415
#define CLIENT_NUM 5

struct client {
    int client_sock;
    int port;
    int empty;
    pthread_t tid;
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
    pthread_detach(pthread_self());
    int client_sock;
    char buf[DATA_LEN];
    char port[DATA_LEN];
    struct client* client = (struct client*)arg;
    int server_sock;
    struct sockaddr_in client_sockaddr;
    struct sockaddr_in server_sockaddr;
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
    sprintf(port, "%d", client->port);
    if (send(client->client_sock, port, DATA_LEN, 0) == -1) {
        fprintf(stderr, "SEND PORT ERROR\n");
        close(server_sock);
        close(client->client_sock);
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
    client->empty = 0;
    close(client->client_sock);
    close(server_sock);
    close(client_sock);
    return NULL;
}

int main(void) {
    int server_sock, client_sock, len;
    struct sockaddr_in server_sockaddr;
    struct sockaddr_in client_sockaddr;
    struct client clients[CLIENT_NUM];
    for (int i = 0; i < CLIENT_NUM; i++) {
        clients[i].port = PORT + i + 1;
        clients[i].empty = 0;
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
    int n = 0;
    while (n != 8) {
        if ((client_sock = accept(server_sock, (struct sockaddr *) &client_sockaddr, (socklen_t *)&len)) == -1) {
            fprintf(stderr, "ACCEPT ERROR\n");
        } else {
            n++;
            printf("Client socket ip: %s, port: %d\n", inet_ntoa(client_sockaddr.sin_addr), ntohs(client_sockaddr.sin_port));
            for (int i = 0; i < CLIENT_NUM; i++) {
                if (clients[i].empty == 0) {
                    clients[i].empty = 1;
                    clients[i].client_sock = client_sock;
                    pthread_create(&clients[i].tid, NULL, work_with_client, (void*)&(clients[i]));
                    break;
                }
            }
            
        }
    }
    close(server_sock);
    return 0;
}
