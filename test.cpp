#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <fcntl.h>
#include <iostream>
#define content_length 100
#define MAX_CLIENTS 1000

int main(int argc, char **argv)
{
    int n;
    int listen_fd, conn_fd, nready;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t cli_len;
    char buf[content_length];
    int i, j, client_count = 0;

    // create listening socket
    if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket error");
        exit(1);
    }
    if (fcntl(listen_fd, F_SETFL, O_NONBLOCK) < 0)
    {
        perror("fcntl error");
        exit(1);
    }
    int yes = 1;
    if (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &yes,
                   sizeof(int)) == -1)
    {
        perror("setsockopt");
        exit(1);
    } // set up server address
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(9030);

    // bind listening socket to server address
    if (bind(listen_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("bind error");
        exit(1);
    }

    // listen for incoming connections
    if (listen(listen_fd, 10) < 0)
    {
        perror("listen error");
        exit(1);
    }
    // initialize clients array with listening socket]
    struct pollfd clients[MAX_CLIENTS];
    for (i = 0; i < MAX_CLIENTS; i++)
    {
        clients[i].fd = -1;
    }
    clients[0].fd = listen_fd;
    clients[0].events = POLLIN | POLLOUT;

    int flag = 0;
    std::string message;

    while (true)
    {
        std::cout << "----------------\n";
        nready = poll(clients, client_count + 1, -1);
        if (nready < 0)
        {
            perror("poll error");
            continue;
        }

        // check for activity on listening socket
        if (clients[0].revents & POLLIN)
        {
            cli_len = sizeof(cli_addr);
            conn_fd = accept(listen_fd, (struct sockaddr *)&cli_addr, &cli_len);
            if (conn_fd < 0)
            {
                perror("accept error");
                continue;
            }
            if (fcntl(conn_fd, F_SETFL, O_NONBLOCK) < 0)
            {
                perror("fcntl error");
                exit(1);
            }
            // add new client to array
            for (i = 1; i < MAX_CLIENTS; i++)
            {
                if (clients[i].fd < 0)
                {
                    clients[i].fd = conn_fd;
                    clients[i].events = POLLIN;
                    client_count++;
                    break;
                }
            }
            if (i == MAX_CLIENTS)
            {
                fprintf(stderr, "too many clients\n");
                close(conn_fd);
                continue;
            }

            printf("new connection from %s:%d (fd=%d)\n",
                   inet_ntoa(cli_addr.sin_addr),
                   ntohs(cli_addr.sin_port), conn_fd);
        }

        // check for activity on client sockets
        for (i = 1; i <= client_count; i++)
        {
            if (clients[i].revents & POLLIN)
            {
                // clients[i].events = POLLIN ;
                bzero(buf, sizeof(buf));
                if ((n = recv(clients[i].fd, buf, sizeof(buf), 0)) < 0)
                {
                    if (n == -1)
                    {
                        perror("read error");
                    }
                    continue;
                }
                if (n == 0)
                {
                    printf("client %d closed connection\n", clients[i].fd);
                    close(clients[i].fd);
                    clients[i].fd = -1;
                    continue;
                }
                message.append(buf, n);
                // std::cout << message;
                // if (message.length() == 832)
                // {
                int j = 0;
                // if (message.length() == 17025)
                if (message.find("\r\n\r\n") != std::string::npos)
                {
                    // while (j < message.length())
                    // {
                    //     if (message.find("\r\n\r\n") != std::string::npos)
                    //     {
                    clients[i].events = POLLOUT;
                    std::cout << message;
                    std::cout << message.length() << std::endl;
                    // break;
                    //     }
                    //     j++;
                }
            }
            // process HTTP request and send response
            // in this example, we just send a "hello world" response
            if (clients[i].revents & POLLOUT)
            {
                std::string msg;
                msg += "HTTP/1.1 200 OK\r\n";
                msg += "Content-Type: text/plain\r\n";
                msg += "Content-Length: 12\r\n";
                msg += "\r\n";
                msg += "hello world\n";
                // if (send(clients[i].fd, msg.c_str(), msg.length(), 0) < 0)
                // {
                send(clients[i].fd, msg.c_str(), msg.length(),0 );
                // perror("write error");
                close(clients[i].fd);
                clients[i].fd = -1;
                //     continue;
                // }
                message.clear();
            }
        }

        // remove closed client sockets from array
        // for (i = 1; i <= client_count; i++)
        // {
        //     if (clients[i].fd < 0)
        //     {
        //         for (j = i; j < client_count; j++)
        //         {
        //             clients[j].fd = clients[j + 1].fd;
        //         }
        //         client_count--;
        //         i--;
        //     }
        // }
    }
}