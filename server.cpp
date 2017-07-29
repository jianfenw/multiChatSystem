#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <thread>
#define PORT 7000
#define BACKLOG 10
#define QUEUE 20
int conn;

int main() {
    std::cout << "Hello, World!" << std::endl;

    std::cout << AF_INET << std::endl;
    std::cout << SOCK_STREAM << std::endl;
    std::cout << SOCK_DGRAM << std::endl;
    std::cout << INADDR_ANY << std::endl;

    int sockfd, rv;
    int status=0;
    int yes = 0, bytes = 0;
    struct addrinfo hints;
    struct addrinfo *res, *p;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    // For client address storage
    struct sockaddr_storage client_addr; // to store the client's address
    socklen_t addr_size = sizeof(client_addr);

    if ( (rv = getaddrinfo(NULL, "7000", &hints, &res)) != 0){
        perror("Error: cannot use the port number");
        exit(1);
    }
    for (p=res; p != NULL; p = p->ai_next){
        if ( (sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            continue;
        }
        if ( (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes))) == -1){
            close(sockfd);
            perror("Error: setsockopt");
            exit(1);
        }
        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1){
            close(sockfd);
            perror("Error: bind");
            exit(1);
        }
        break;
    }
    if (NULL == p){
        perror("Error: bind failed");
        exit(1);
    }
    freeaddrinfo(res);
    res = NULL;

    std::cout << "The server is up and running" << std::endl;
    if ((status = listen(sockfd, BACKLOG)) == -1){
        perror("Error: listen");
        exit(1);
    }

    while(1){
        conn = accept(sockfd, (struct sockaddr*)&client_addr, &addr_size);
        if (conn == -1){
            perror("Error: accept");
            continue;
        }
        char buf[1024];
        if ( (bytes = recv(conn, buf, sizeof(buf), 0)) == -1){
            close(sockfd);
            perror("Error: recv");
            exit(1);
        }
        buf[bytes] = '\0';
        //std::cout << buf << std::endl << strcmp(buf, "exit") << std::endl;
        if (strcmp(buf, "exit") == 0){
            break;
        }
        else{
            std::cout << buf << std::endl;
            continue;
        }
    }

    close(sockfd);
    close(conn);

    return 0;
}