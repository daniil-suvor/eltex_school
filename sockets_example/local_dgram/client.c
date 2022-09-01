/************************************************************/
/* This is a stream socket client sample program for LOCAL  */
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

#define SERVER_PATH "local_dgram_sock.server"
#define CLIENT_PATH "local_dgram_sock.client"
#define DATA "Hello from client"
#define DATA_LEN 256

int main(void) {
    int client_sock, len;
    struct sockaddr_un server_sockaddr; 
    struct sockaddr_un client_sockaddr; 
    char buf[DATA_LEN];
     
    /***************************************/
    /* Create a LOCAL domain stream socket */
    /***************************************/
    if ((client_sock = socket(AF_LOCAL, SOCK_DGRAM, 0)) == -1) {
        fprintf(stderr, "SOCKET ERROR\n");
        exit(1);
    }

    /****************************************/
    /* Set up the LOCAL sockaddr structure  */
    /* by using AF_LOCAL for the family and */
    /* giving it a filepath to bind to.     */
    /****************************************/

    client_sockaddr.sun_family = AF_LOCAL;   
    strcpy(client_sockaddr.sun_path, CLIENT_PATH); 
    len = sizeof(client_sockaddr);
    
    if (bind(client_sock, (struct sockaddr*)&client_sockaddr, len) == -1) {
        fprintf(stderr, "BIND ERROR\n");
        close(client_sock);
        unlink(CLIENT_PATH);
        exit(1);
    }
        
    /***************************************/
    /* Set up the LOCAL sockaddr structure */
    /* for the server socket and connect   */
    /* to it.                              */
    /***************************************/
    server_sockaddr.sun_family = AF_LOCAL;
    strcpy(server_sockaddr.sun_path, SERVER_PATH);
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
