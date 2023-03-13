#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include<string>
#include<vector>
#include <map>
#include<iostream>
int main()
{
    std::map<std::string, std::string > my;
    std::vector <std::string> ve;
    ve.push_back("hel");
    my.insert(std::make_pair("x1", "1"));
    my.insert(std::make_pair("1ello2", "1"));
    my.insert(std::make_pair("cello4", "1"));
    my.insert(std::make_pair("aello5", "1"));
    std::map<std::string, std::string >::iterator it = my.begin();
    int i = 0;
    while (it != my.end())
    {
        std::cout<<it->first<<std::endl;
        it++;
    }
    
}

// #define MAX_EVENTS 10
// #define BUFFER_SIZE 1024

// int main(int argc, char *argv[])
// {
//     int port1 = 8081;
//     int port2 = 8083;
//     int optval;
//     struct sockaddr_in addr1, addr2;

//     // Create socket file descriptors
//     int fd1 = socket(AF_INET, SOCK_STREAM, 0);
//     setsockopt(fd1, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int));

//     memset(&addr1, 0, sizeof(addr1));
//     addr1.sin_family = AF_INET;
//     addr1.sin_addr.s_addr = htonl(INADDR_ANY);
//     addr1.sin_port = htons(port1);

//     // Create sockaddr_in structures for the two ports

//     int fd2 = socket(AF_INET, SOCK_STREAM, 0);
//     setsockopt(fd2, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int));
//     memset(&addr2, 0, sizeof(addr2));
//     addr2.sin_family = AF_INET;
//     addr2.sin_addr.s_addr = htonl(INADDR_ANY);
//     addr2.sin_port = htons(port2);

//     if (fd1 < 0 || fd2 < 0)
//     {
//         perror("socket");
//         exit(1);
//     }
//     // Bind the sockets to the ports
//     if (bind(fd1, (struct sockaddr *)&addr1, sizeof(addr1)) < 0)
//     {
//         perror("bind1");
//         exit(1);
//     }

//     if (bind(fd2, (struct sockaddr *)&addr2, sizeof(addr2)) < 0)
//     {
//         perror("bind2");
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
//     char buffer[BUFFER_SIZE];
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
//                     if (read(newfd, buffer, BUFFER_SIZE) < 0)
//                     {
//                         perror("read");
//                         exit(1);
//                     }

//                     const char *response = "HTTP/1.1 200 OK\r\nContent-Length: 12\r\n\r\nHello World form 8082!";
//                     if (write(newfd, response, strlen(response)) < 0)
//                     {
//                         perror("write");
//                         exit(1);
//                     }
//                     close(newfd);
//                 }
//                 else if (i == fd2)
//                 {
//                     struct sockaddr_in cliaddr;
//                     socklen_t clilen = sizeof(cliaddr);
//                     int newfd = accept(fd2, (struct sockaddr *)&cliaddr, &clilen);
//                     if (read(newfd, buffer, BUFFER_SIZE) < 0)
//                     {
//                         perror("read");
//                         exit(1);
//                     }

//                     // Send the HTTP response to the client
//                     const char *response = "HTTP/1.1 200 OK\r\nContent-Length: 12\r\n\r\nHello World from 8083!";
//                     if (write(newfd, response, strlen(response)) < 0)
//                     {
//                         perror("write");
//                         exit(1);
//                     }
//                     close(newfd);
//                 }
//                 // Handle incoming connections on
//             }
//         }
//     }
//     return 0;
// }
