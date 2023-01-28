#ifndef WEBSERV_HPP
#define WEBSERV_HPP

//    define variables //

// -------  cpp -----//
#include <iostream>

// ------    c   ----//
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>  /* See NOTES */
#include <netinet/in.h> // for type (struct sockaddr_in)
#include <unistd.h>
#include <fcntl.h>

#include <arpa/inet.h>

class Webserv
{
private:
    int port;
    int sockfd;
    int backlog; // a maximum pending connections for master socket
    struct sockaddr_in serv_addr;

public:
    int msg_error(int status)
    {
        std::cout << "errrorrr  " << status << std::endl;
        return -1;
    }
    int init_server()
    {
        this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
        std::cout << sockfd;
        if (this->sockfd == -1)
            return msg_error(0);
        this->serv_addr.sin_family = AF_INET;
        this->serv_addr.sin_port = htons(this->port);
        this->serv_addr.sin_addr.s_addr = INADDR_ANY;

        // bind the socket to localhost port 5500
        if (bind(this->sockfd, (struct sockaddr *)(&this->serv_addr), sizeof(this->serv_addr)) == -1)
            return msg_error(1);
        if (listen(this->sockfd, this->backlog) == -1)
            return msg_error(2);
        return 0;
    }

    int run_server()
    {
        int var = sizeof(this->serv_addr);
        std::cout << sizeof(socklen_t);
        int fd_client;
        // while (true)
        // {
        fd_client = accept(this->sockfd, (struct sockaddr *)&(this->serv_addr), (socklen_t *)&var);
        if (-1 == fd_client)
            return msg_error(3);
        std::string str;
        str = "HTTP/1.1 200 OK\r\n\r\n";
        str += "<!DOCTYPE html>\n";
        str += "<html>\n";
        str += "    <head>\n";

        str += "        <title>Cerveur</title>\n";
        str += "   </head>\n";
        str += "    <body><h1>Index page</h1>\n";
        str += "    </body>\n";
        str += "</html>\n";
        str += "\r\n\r\n";
        char buf[1024];
        recv(this->sockfd,buf,1024,0);
        std::cout<<buf;
        if (send(this->sockfd, str.c_str(), str.length(), 0) != str.length())
            return msg_error(4);
        close(this->sockfd);
        std::cout << "connected\n";
        // }
        return 0;
    }
    Webserv()
    {
    }
    Webserv(int prt, int backlg)
    {
        this->port = prt;
        this->backlog = backlog;
    }
    ~Webserv()
    {
    }
};

#endif
