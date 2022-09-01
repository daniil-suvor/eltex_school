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

#define SERVER_PATH "inet_dgram_sock.server"
#define CLIENT_PATH "inet_dgram_sock.client"
#define DATA "Hello from client"
#define DATA_LEN 256
#define PORT_CLIENT 27182
#define PORT_SERVER 31415

int main(void) {
    int client_sock, len;
    struct sockaddr_in server_sockaddr; 
    struct sockaddr_in client_sockaddr; 
    char buf[DATA_LEN];
     
    /***************************************/
    /* Create a INET domain stream socket  */
    /***************************************/
    if ((client_sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        fprintf(stderr, "SOCKET ERROR\n");
        exit(1);
    }

    /***************************************/
    /* change socket options for should    */ 
    /* allow reuse of local addresses.     */
    /***************************************/
    int optval = 1;
    if (setsockopt(client_sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1) {
        printf("SETSOCKETOPT ERROR\n");
        exit(1);
    }

    /****************************************/
    /* Set up the INET sockaddr structure   */
    /* by using AF_INET for the family and  */
    /* giving it a filepath to bind to.     */
    /****************************************/

    client_sockaddr.sin_family = AF_INET;
    client_sockaddr.sin_port = htons(PORT_CLIENT);
    client_sockaddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    len = sizeof(client_sockaddr);
    
    if (bind(client_sock, (struct sockaddr*)&client_sockaddr, len) == -1) {
        fprintf(stderr, "BIND ERROR\n");
        close(client_sock);
        unlink(CLIENT_PATH);
        exit(1);
    }
        
    /***************************************/
    /* Set up the INET sockaddr structure  */
    /* for the server socket and connect   */
    /* to it.                              */
    /***************************************/
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(PORT_SERVER);
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    len = sizeof(server_sockaddr);
    if (connect(client_sock, (struct sockaddr *)&server_sockaddr, len) == -1) {
        fprintf(stderr, "CONNECT ERROR\n");
        close(client_sock);
        unlink(CLIENT_PATH);
        exit(1);
    }
    
    /************************************/
    /* Copy the data to the buffer and  */
    /* send it to the server socket.    */
    /************************************/
    strcpy(buf, DATA);                 
    printf("Sending data...\n");
    if (sendto(client_sock, buf, strlen(buf), 0, (struct sockaddr*)&server_sockaddr, len) == -1) {
        fprintf(stderr, "SEND ERROR\n");
        close(client_sock);
        unlink(CLIENT_PATH);
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
    if (recvfrom(client_sock, buf, DATA_LEN, 0, (struct sockaddr *)&server_sockaddr, (socklen_t *)&len) == -1) {
        fprintf(stderr, "RECV ERROR\n");
        close(client_sock);
        unlink(CLIENT_PATH);
        exit(1);
    } else {
        printf("DATA RECEIVED = %s\n", buf);
    }
    
    /******************************/
    /* Close the socket and exit. */
    /******************************/
    close(client_sock);
    /****************************************/
    /* Unlink the file so the bind will     */
    /* succeed, then bind to that file.     */
    /****************************************/
    unlink(CLIENT_PATH);
    return 0;
}
