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
#include <vector>
#define content_length 100
#define MAX_CLIENTS 1000
#include <map>
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
    if (bind(listen_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("bind error");
        exit(1);
    }
    if (listen(listen_fd, 10) < 0)
    {
        perror("listen error");
        exit(1);
    }
    std::vector<pollfd> clients;

    // clients[0].
    pollfd clie;
    clie.fd = listen_fd;
    clie.events = POLLIN | POLLOUT;
    clients.push_back(clie);
    int flag = 0;
    std::string message;
    std::map<int, std::string> clit;
    while (true)
    {

        std::cout << "----------------\n";
        for (std::map<int, std::string>::iterator it = clit.begin(); it != clit.end(); it++)
            std::cout << it->first << " ";
        std::cout << "\n";
        nready = poll(clients.data(), clients.size(), -1);
        if (nready < 0)
        {
            perror("poll error");
            continue;
        }
        if (clients[0].revents & POLLIN)
        {
            cli_len = sizeof(cli_addr);
            pollfd cfd;
            cfd.fd = accept(listen_fd, (struct sockaddr *)&cli_addr, &cli_len);
            if (cfd.fd < 0)
            {
                perror("accept error");
                continue;
            }
            if (fcntl(cfd.fd, F_SETFL, O_NONBLOCK) < 0)
            {
                perror("fcntl error");
                exit(1);
            }
            cfd.events = POLLIN;
            clit.insert(std::make_pair(cfd.fd, "config"));
            clients.push_back(cfd);
            std::cout << "New client connected\n";
            flag = 1;
            if (i == MAX_CLIENTS)
            {
                fprintf(stderr, "too many clients\n");
                close(conn_fd);
                continue;
            }
        }
        for (i = 1; i <= client_count; i++)
        {
            if (clients[i].revents & POLLIN)
            {
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
                int j = 0;
                if (message.find("\r\n\r\n") != std::string::npos)
                {
                    clients[i].events = POLLOUT;
                    std::cout << message;
                    std::cout << message.length() << std::endl;
                }
            }
            if (clients[i].revents & POLLOUT)
            {
                std::string msg;
                msg += "HTTP/1.1 200 OK\r\n";
                msg += "Content-Type: text/plain\r\n";
                msg += "Content-Length: 12\r\n";
                msg += "\r\n";
                time_t tm = time(NULL);
                if (tm % 2)
                    msg += "hello world\n";

                else
                    msg += "waxch khadm\n";
                send(clients[i].fd, msg.c_str(), msg.length(), 0);
                close(clients[i].fd);
                clients.erase(clients.begin() + i);
                clit.erase(clit.find(clients[i].fd));
                client_count--;
                message.clear();
            }
        }
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