/************************************************************/
/* This is a stream socket server sample program for LOCAL  */
/* domain sockets. This program listens for a connection    */
/* from a client program, accepts it, reads data from the   */
/* client, then sends data back to connected LOCAL socket.  */
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

#define SOCK_PATH  "local_stream_sock.server"
#define DATA "Hello from server"
#define DATA_LEN 256

int main(void) {
    int server_sock, client_sock, len;
    struct sockaddr_un server_sockaddr;
    struct sockaddr_un client_sockaddr;     
    char buf[DATA_LEN];
    int backlog = 10;
    
    /***************************************/
    /* Create a LOCAL domain stream socket */
    /***************************************/
    if ((server_sock = socket(AF_LOCAL, SOCK_STREAM, 0)) == -1){
        printf("SOCKET ERROR\n");
        exit(1);
    }
    
    /****************************************/
    /* Set up the LOCAL sockaddr structure  */
    /* by using AF_LOCAL for the family and */
    /* giving it a filepath to bind to.     */
    /****************************************/
    server_sockaddr.sun_family = AF_LOCAL;   
    strcpy(server_sockaddr.sun_path, SOCK_PATH); 
    len = sizeof(server_sockaddr);
    
    if (bind(server_sock, (struct sockaddr *) &server_sockaddr, len) == -1){
        fprintf(stderr, "BIND ERROR\n");
        close(server_sock);
        unlink(SOCK_PATH);
        exit(1);
    }
    
    /*********************************/
    /* Listen for any client sockets */
    /*********************************/
    if (listen(server_sock, backlog) == -1){ 
        fprintf(stderr, "LISTEN ERROR\n");
        close(server_sock);
        unlink(SOCK_PATH);
        exit(1);
    }
    printf("socket listening...\n");
    
    /*********************************/
    /* Accept an incoming connection */
    /*********************************/
    if ((client_sock = accept(server_sock, (struct sockaddr *) &client_sockaddr, (socklen_t *)&len)) == -1) {
        fprintf(stderr, "ACCEPT ERROR\n");
        close(server_sock);
        close(client_sock);
        unlink(SOCK_PATH);
        exit(1);
    }
    
    /****************************************/
    /* Get the name of the connected socket */
    /****************************************/
    len = sizeof(client_sockaddr);
    if (getpeername(client_sock, (struct sockaddr *) &client_sockaddr, (socklen_t *)&len) == -1) {
        fprintf(stderr, "GETPEERNAME ERROR\n");
        close(server_sock);
        close(client_sock);
        unlink(SOCK_PATH);
        exit(1);
    } else {
        printf("Client socket filepath: %s\n", client_sockaddr.sun_path);
    }
    
    /************************************/
    /* Read and print the data          */
    /* incoming on the connected socket */
    /************************************/
    printf("waiting to read...\n");
    if (recv(client_sock, buf, sizeof(buf), 0) == -1) {
        fprintf(stderr, "RECV ERROR\n");
        close(server_sock);
        close(client_sock);
        unlink(SOCK_PATH);
        exit(1);
    } else {
        printf("DATA RECEIVED = %s\n", buf);
    }
    
    /******************************************/
    /* Send data back to the connected socket */
    /******************************************/
    memset(buf, 0, strlen(buf));
    strcpy(buf, DATA);      
    printf("Sending data...\n");
    if (send(client_sock, buf, strlen(buf), 0) == -1) {
        fprintf(stderr, "SEND ERROR\n");
        close(server_sock);
        close(client_sock);
        unlink(SOCK_PATH);
        exit(1);
    } else {
        printf("Data sent!\n");
    }
    
    /******************************/
    /* Close the sockets and exit */
    /******************************/
    close(server_sock);
    close(client_sock);
    /****************************************/
    /* Unlink the file so the bind will     */
    /* succeed, then bind to that file.     */
    /****************************************/
    unlink(SOCK_PATH);
    return 0;
}
