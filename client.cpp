//
// Created by Jianfeng Wang on 7/28/17.
//

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <thread>
#include <netdb.h>

#define PORT 7000
#define QUEUE 20
#define MAXBUFFERSIZE 8 * 3000
#define S_PORT_NUM "7000"
int conn;

int connect_to_server();



/*
 * Client:
 * Boot up and print boot-up message
 * Establish a TCP connection with the server host
 * 1. Send the <init hello message> to the server and wait for the server's response
 * 2. Talk anything and should receive the echo message from the server
 * 3. End the connection with a single message "END"
 */

int main(int argc, char const *argv[]){
    int client_fd = 0;
    int bytes = 0;
    char send_buf[MAXBUFFERSIZE], recv_buf[MAXBUFFERSIZE];

    strncpy(send_buf, argv[1], strlen(argv[1]));
    send_buf[strlen(argv[1])] = '\0';
    std::cout << send_buf << " " << strlen(send_buf) << " " << sizeof(send_buf) << std::endl;

    std::cout << "The client is up and running\n" << std::endl;

    // After booting up, the client establishes a TCP connection with AWS

    if (!(client_fd = connect_to_server())) {
        fprintf(stderr, "Error: connection failed\n");
        exit(1);
    }

    bytes = send(client_fd, send_buf, strlen(send_buf), 0);
    if (bytes == -1){
        close(client_fd);
        perror("Error: send");
        exit(1);
    }
    else{
        std::cout << bytes << std::endl;
    }


    close(client_fd);

    return 0;
}

int connect_to_server(){
    int fd, rv;
    struct addrinfo hints;
    struct addrinfo *res, *p;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if ( (rv = getaddrinfo("localhost", S_PORT_NUM, &hints, &res)) != 0){
        perror("Error: getaddrinfo");
        exit(1);
    }
    for (p=res; p != NULL; p = p->ai_next){
        void *addr;
        char *ipver;
        std::cout << p->ai_family << " " << AF_INET << std::endl;
        if (p->ai_family == AF_INET){
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPV4";
        }
        else{
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPV6";
        }
        std::cout << addr << " " << ipver << std::endl;
        if ( (fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1){
            perror("Error: socket");
            continue;
        }
        if ( (connect(fd, p->ai_addr, p->ai_addrlen)) == -1){
            close(fd);
            perror("Error: connect");
            exit(2);
        }
        break;
    }
    if (NULL == p){
        perror("Error: fail to connect");
        exit(3);
    }
    freeaddrinfo(res);
    res = NULL;
    return fd;
}




