

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <iostream>
#define MAX_EVENTS 10
#define BUFFER_SIZE 1024
int ft_exit(std::string a)
{
    perror(a.c_str());
    exit(1);
}
int main(int ac, char **av)
{
    int i = 1;
    std::vector<int> config;
    while (av[i])
    {
        config.push_back(atoi(av[i]));
        i++;
    }
    i = 0;
    std::map<int, std::vector<int>> stack;
    int optval = 1;
    int sockfd;
    while (i < config.size())
    {
        std::cout << config[i] << std::endl;
        struct sockaddr_in serv_addr;
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        // for solve problem (address already in use)
        if ((setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int))) == -1)
        {
            perror("socket error\n");
            return -1;
        }
        if (sockfd == -1)
            ft_exit("0");
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(config[i]);
        serv_addr.sin_addr.s_addr = INADDR_ANY;

        // bind the socket to localhost port 5500
        if (bind(sockfd, (struct sockaddr *)(&serv_addr), sizeof(serv_addr)) == -1)
            ft_exit("1");
        if (listen(sockfd, 5) == -1)
            ft_exit("2");
        stack.insert(std::make_pair(sockfd, config[i]));
        i++;
    }
    int fd_max = sockfd;

    fd_set readd;
    FD_ZERO(&readd);
    i = 0;
    for (std::map<int, std::vector<int>>::iterator it = stack.begin(); it != stack.end(); it++)
        FD_SET(it->first, &readd);
    printf("readyy-----\n\n");
    while (1)
    {
        fd_set tmp_fds = readd;
        if (select(fd_max + 1, &tmp_fds, NULL, NULL, NULL) < 0)
        {
            perror("select");
            exit(1);
        }
        for (std::map<int, std::vector<int>>::iterator it = stack.begin(); it != stack.end(); it++)
        {
            // if (i == it->first)
            if (FD_ISSET(it->first, &tmp_fds))
            {
                // Handle incoming connections on port1
                struct sockaddr_in cliaddr;
                socklen_t clilen = sizeof(cliaddr);
                int newfd = accept(it->first, (struct sockaddr *)&cliaddr, &clilen);

                if (newfd < 0)
                {
                    perror("accept");
                    exit(1);
                }

                // Do something with the connection on port1
                char buffer[BUFFER_SIZE];
                if (read(newfd, buffer, BUFFER_SIZE) < 0)
                {
                    perror("read");
                    exit(1);
                }
                printf("from: %d\n", it->second[0]);

                std::string response = "HTTP/1.1 200 OK\r\n\r\n\r\n" + std::to_string(it->second[1]) + "\n";
                if (write(newfd, response.c_str(), strlen(response.c_str())) < 0)
                {
                    perror("write");
                    exit(1);
                }
                close(newfd);
            }
        }
    }
}

// int main(int argc, char *argv[])
// {
//     std::vector<int> vect;
//     if (argc != 3)
//     {
//         printf("Usage: %s port1 port2\n", argv[0]);
//         exit(1);
//     }

//     int port1 = atoi(argv[1]);
//     vect.push_back(port1);
//     int port2 = atoi(argv[2]);
//     vect.push_back(port2);

//     // Create socket file descriptors
//     int fd1 = socket(AF_INET, SOCK_STREAM, 0);
//     int fd2 = socket(AF_INET, SOCK_STREAM, 0);

//     if (fd1 < 0 || fd2 < 0)
//     {
//         perror("socket");
//         exit(1);
//     }

//     // Create sockaddr_in structures for the two ports
//     struct sockaddr_in addr1, addr2;
//     memset(&addr1, 0, sizeof(addr1));
//     memset(&addr2, 0, sizeof(addr2));

//     addr1.sin_family = AF_INET;
//     addr2.sin_family = AF_INET;

//     addr1.sin_port = htons(port1);
//     addr2.sin_port = htons(port2);

//     addr1.sin_addr.s_addr = INADDR_ANY;
//     addr2.sin_addr.s_addr = INADDR_ANY;

//     // Bind the sockets to the ports
//     if (bind(fd1, (struct sockaddr *)&addr1, sizeof(addr1)) < 0)
//     {
//         perror("bind");
//         exit(1);
//     }

//     if (bind(fd2, (struct sockaddr *)&addr2, sizeof(addr2)) < 0)
//     {
//         perror("bind");
//         exit(1);
//     }

//     // Listen on the ports
//     if (listen(fd1, 5) < 0)
//     {
//         perror("listen");
//         exit(1);
//     }

//     if (listen(fd2, 5) < 0)
//     {
//         perror("listen");
//         exit(1);
//     }

//     // Create an array of file descriptors to use with select()
//     fd_set rfds;
//     FD_ZERO(&rfds);
//     FD_SET(fd1, &rfds);
//     FD_SET(fd2, &rfds);

//     int maxfd = fd1 > fd2 ? fd1 : fd2;

//     while (1)
//     {
//         fd_set tmp_fds = rfds;
//         if (select(maxfd + 1, &tmp_fds, NULL, NULL, NULL) < 0)
//         {
//             perror("select");
//             exit(1);
//         }

//         for (int i = 0; i <= maxfd; i++)
//         {
//             if (FD_ISSET(i, &tmp_fds))
//             {
//                 if (i == fd1)
//                 {
//                     // Handle incoming connections on port1
//                     struct sockaddr_in cliaddr;
//                     socklen_t clilen = sizeof(cliaddr);
//                     int newfd = accept(fd1, (struct sockaddr *)&cliaddr, &clilen);

//                     if (newfd < 0)
//                     {
//                         perror("accept");
//                         exit(1);
//                     }

//                     // Do something with the connection on port1
//                     char buffer[BUFFER_SIZE];
//                     if (read(newfd, buffer, BUFFER_SIZE) < 0)
//                     {
//                         perror("read");
//                         exit(1);
//                     }
//                     printf("from: %d\n", port1);
//                     const char *response = "HTTP/1.1 200 OK\r\nContent-Length: 12\r\n\r\nHello World!";
//                     if (write(newfd, response, strlen(response)) < 0)
//                     {
//                         perror("write");
//                         exit(1);
//                     }
//                     close(newfd);
//                 }
//                 else if (i == fd2)
//                 {
//                     // Handle incoming connections on port1
//                     struct sockaddr_in cliaddr;
//                     socklen_t clilen = sizeof(cliaddr);
//                     int newfd = accept(fd2, (struct sockaddr *)&cliaddr, &clilen);

//                     if (newfd < 0)
//                     {
//                         perror("accept");
//                         exit(1);
//                     }

//                     // Do something with the connection on port1
//                     char buffer[BUFFER_SIZE];
//                     if (read(newfd, buffer, BUFFER_SIZE) < 0)
//                     {
//                         perror("read");
//                         exit(1);
//                     }

//                     // Send the HTTP response to the client
//                     printf("from: %d\n", port2);
//                     const char *response = "HTTP/1.1 200 OK\r\nContent-Length: 12\r\n\r\nHello World!";
//                     if (write(newfd, response, strlen(response)) < 0)
//                     {
//                         perror("write");
//                         exit(1);
//                     }
//                     close(newfd);
//                 }
//             }
//         }
//     }
// }
