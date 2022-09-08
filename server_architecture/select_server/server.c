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

#define DATA "Hello from server"
#define DATA_LEN 256
#define PORT_TCP 31415
#define PORT_UDP 3141

int create_socket(int type, struct sockaddr_in* new_sock, int port, uint32_t ip_adr) {
    int sock;
    int len = sizeof(struct sockaddr_in);

    /***************************************/
    /* Create a INET domain stream socket  */
    /***************************************/
    if ((sock = socket(AF_INET, type, 0)) == -1){
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
void tcp_server(int server_sock) {
    int client_sock, len;
    struct sockaddr_in client_sockaddr;     
    char buf[DATA_LEN];
    len = sizeof(struct sockaddr_in);
    
    /*********************************/
    /* Accept an incoming connection */
    /*********************************/
    if ((client_sock = accept(server_sock, (struct sockaddr *) &client_sockaddr, (socklen_t *)&len)) == -1) {
        fprintf(stderr, "ACCEPT ERROR\n");
        close(server_sock);
        close(client_sock);
        exit(1);
    } else {
        printf("Client socket ip: %s, port: %d\n", inet_ntoa(client_sockaddr.sin_addr), ntohs(client_sockaddr.sin_port));
    }
        
    /************************************/
    /* Read and print the data          */
    /* incoming on the connected socket */
    /************************************/
    printf("waiting to read...\n");
    if (recv(client_sock, buf, DATA_LEN, 0) == -1) {
        fprintf(stderr, "RECV ERROR\n");
        close(server_sock);
        close(client_sock);
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
    if (send(client_sock, buf, DATA_LEN, 0) == -1) {
        fprintf(stderr, "SEND ERROR\n");
        close(server_sock);
        close(client_sock);
        exit(1);
    } else {
        printf("Data sent!\n");
    }
    
    /******************************/
    /* Close the sockets and exit */
    /******************************/
    close(server_sock);
    close(client_sock);
}
void udp_server(int server_sock) {
    int len;
    struct sockaddr_in client_sockaddr;     
    char buf[DATA_LEN];
    len = sizeof(struct sockaddr_in);
    /************************************/
    /* Waite connect any socket         */
    /* Get struct sockaddr* client for  */
    /* get the name of the connected    */
    /* socket and send message          */
    /************************************/
    printf("waiting to read...\n");
    if (recvfrom(server_sock, buf, DATA_LEN, 0, (struct sockaddr *)&client_sockaddr, (socklen_t *)&len) == -1) {
        fprintf(stderr, "RECV ERROR\n");
        close(server_sock);
        exit(1);
    } else {
        printf("Client socket ip: %s, port: %d\n", inet_ntoa(client_sockaddr.sin_addr), ntohs(client_sockaddr.sin_port));
        printf("DATA RECEIVED = %s\n", buf);
    }
    
    /******************************************/
    /* Send data back to the connected socket */
    /******************************************/
    memset(buf, 0, strlen(buf));
    strcpy(buf, DATA);
    printf("Sending data...\n");
    if (sendto(server_sock, buf, DATA_LEN, 0, (struct sockaddr *)&client_sockaddr, len) == -1) {
        fprintf(stderr, "SEND ERROR\n");
        close(server_sock);
        exit(1);
    } else {
        printf("Data sent!\n");
    }
    
    /******************************/
    /* Close the sockets and exit */
    /******************************/
    close(server_sock);
}
int main(void) {
    int server_udp, server_tcp, retval;
    struct sockaddr_in server_sockaddr;
    fd_set rfds;
    
    server_tcp = create_socket(SOCK_STREAM, &server_sockaddr, PORT_TCP, INADDR_LOOPBACK);
    if (server_tcp == -1) {
        exit(0);
    }
    if (listen(server_tcp, 1) == -1){ 
        fprintf(stderr, "LISTEN ERROR\n");
        close(server_tcp);
        exit(1);
    }
    printf("socket listening...\n");
    server_udp = create_socket(SOCK_DGRAM, &server_sockaddr, PORT_UDP, INADDR_LOOPBACK);
    if (server_udp == -1) {
        close(server_tcp);
        exit(0);
    }
    FD_ZERO(&rfds);
    FD_SET(server_tcp, &rfds);
    FD_SET(server_udp, &rfds);
    int max_fd = (server_tcp > server_udp) ? server_tcp + 1 : server_udp + 1;
    retval = select(max_fd, &rfds, NULL, NULL, NULL);
    if (retval != -1) {
        if (FD_ISSET(server_tcp, &rfds))
            tcp_server(server_tcp);
        else if (FD_ISSET(server_udp, &rfds))
            udp_server(server_udp);
    } else {
        fprintf(stderr, "SELECT ERROR!\n");
    }
    close(server_udp);
    close(server_tcp);
    return 0;
}
