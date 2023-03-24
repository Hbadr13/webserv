#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <sys/event.h>

int init_socket(int port)
{
    int yes = 1;
    int sockfd;
    struct sockaddr_in serv_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("ERROR opening socket");
        exit(1);
    }
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                   sizeof(int)) == -1)
    {
        perror("ERROR");
        exit(1);
    }
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("ERROR on binding");
        exit(1);
    }

    if (listen(sockfd, 5) < 0)
    {
        perror("ERROR on listen");
        exit(1);
    }
    return sockfd;
}

int main(int argc, char *argv[])
{
    int sockfd = init_socket(9090);
    int max_fd = sockfd;
    fd_set readfds, writefds;
    FD_ZERO(&readfds);
    FD_ZERO(&writefds);
    FD_SET(sockfd, &readfds);
    // FD_SET(1, &readfds);
    struct timeval tv;
    char buf[40000];
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    // while (1)
    // {
    // }
    int bit = select(max_fd + 1, &readfds, &writefds, NULL, NULL);
    for (int i = 0; i <= max_fd; i++)
        std::cout << i << std::endl;
    std::cout << "Connect \n"
              << std::endl;
    int client_fd = accept(sockfd, NULL, NULL);
    FD_SET(client_fd, &readfds);
    bit = select(max_fd + 2, &readfds, &writefds, NULL, NULL);
    std::cout << "ready  \n"
              << std::endl;
    int n;
    bzero(buf, sizeof(buf));
    read(client_fd, buf, sizeof(buf));
    std::cout << buf;
    read(client_fd, buf, sizeof(buf));
    std::cout << buf;
    read(client_fd, buf, sizeof(buf));
    std::cout << buf;
    read(client_fd, buf, sizeof(buf));
    std::cout << buf;
    read(client_fd, buf, sizeof(buf));
    std::cout << buf;
    // while (1)
    //     ;
    // read(client_fd, buf, sizeof(buf));
    // std::cout << buf << std::endl;
    // while (n = read(client_fd, buf, sizeof(buf)))
    // {
    //     std::cout << n;
    //     if (n <= 0)
    //         break;
    // }
}