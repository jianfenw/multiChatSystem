#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <thread>
#define PORT 7000
#define QUEUE 20
int conn;


int main() {
    std::cout << "Hello, World!" << std::endl;

    std::cout << AF_INET << std::endl;
    std::cout << SOCK_STREAM << std::endl;
    std::cout << SOCK_DGRAM << std::endl;
    std::cout << INADDR_ANY << std::endl;

    int ss = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_sockaddr;
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(PORT);
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(ss, (struct sockaddr*) &server_sockaddr, sizeof(server_sockaddr)) == -1){
        perror("Error: bind");
        close(ss);
        exit(1);
    }
    if (listen(ss, QUEUE) == -1){
        perror("Error: listen");
        close(ss);
        exit(2);
    }

    // After receiving the request from the client side
    struct sockaddr_in client_sockaddr;
    socklen_t length = sizeof(client_sockaddr);
    conn = accept(ss, (struct sockaddr*)&client_sockaddr, &length);

    if (conn < 0){
        perror("Error: conn");
        close(ss);
        exit(3);
    }
    close(ss);


    char buf[1024];
    // Create another thread and use it to communicate with the client
    while (1){
        memset(buf, 0, sizeof(buf));
        int len = recv(conn, buf, sizeof(buf), 0);
        if (strcmp(buf, "exit\n") == 0) {
            break;
        }
        else{
            std::cout << buf;
        }
        if(send(conn, buf, sizeof(buf), 0) <= 0){
            perror("Error: send");
            exit(4);
        }
    }

    close(conn);

    return 0;
}