/************************************************************/
/* This is a stream socket client sample program for INET  */
/* domain sockets. This program creates a socket, connects  */
/* to a server, sends data, then receives and prints a      */
/* message from the server.                                 */
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

#define DATA "Hello from client"
#define DATA_LEN 256
#define PORT_CLIENT 27182
#define PORT_SERVER 31415

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
int connect_server(int port, uint32_t ip_adr) {
    struct sockaddr_in server_sockaddr;
    struct sockaddr_in client_sockaddr;
    int len = sizeof(struct sockaddr_in);
    int sock = create_socket(&client_sockaddr, PORT_CLIENT, INADDR_LOOPBACK);
    if (sock == -1) {
        return -1;
    }
    /***************************************/
    /* Set up the INET sockaddr structure  */
    /* for the server socket and connect   */
    /* to it.                              */
    /***************************************/
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(port);
    server_sockaddr.sin_addr.s_addr = htonl(ip_adr);
    if (connect(sock, (struct sockaddr *) &server_sockaddr, len) == -1) {
        fprintf(stderr, "CONNECT ERROR\n");
        close(sock);
        return -1;
    }
    return sock;
}
int main(void) {
    int client_sock;
    char buf[DATA_LEN];    
    client_sock = connect_server(PORT_SERVER, INADDR_LOOPBACK);
    if (client_sock == -1) {
        exit(0);
    }
    if (recv(client_sock, buf, DATA_LEN, 0) == -1) {
        fprintf(stderr, "RECV PORT ERROR\n");
        close(client_sock);
        exit(1);
    } else {
        printf("DATA RECEIVED = %s\n", buf);
        
    }
    close(client_sock);
    client_sock = connect_server(atoi(buf), INADDR_LOOPBACK);
    if (client_sock == -1) {
        exit(0);
    }

    /************************************/
    /* Copy the data to the buffer and  */
    /* send it to the server socket.    */
    /************************************/
    strcpy(buf, DATA);                 
    printf("Sending data...\n");
    if (send(client_sock, buf, strlen(buf), 0) == -1) {
        fprintf(stderr, "SEND ERROR\n");
        close(client_sock);
        exit(1);
    } else {
        printf("Data sent!\n");
    }

    /**************************************/
    /* Read the data sent from the server */
    /* and print it.                      */
    /**************************************/
    printf("Waiting to recieve data...\n");
    memset(buf, 0, strlen(buf));
    if (recv(client_sock, buf, DATA_LEN, 0) == -1) {
        fprintf(stderr, "RECV ERROR\n");
        close(client_sock);
        exit(1);
    } else {
        printf("DATA RECEIVED = %s\n", buf);
    }
    
    /******************************/
    /* Close the socket and exit. */
    /******************************/
    close(client_sock);
    return 0;
}
