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
    //----> getters and setters <--\\.
    int getport();
    void setport(int prt);
    int getsockfd();
    void setsockfd(int sckfd);
    int getbacklog();
    void setbacklog(int backlog);
    
    //---->  memeber fuction <---\\.
    int init_server();
    int run_server();
    Webserv();
    Webserv(int prt, int backlg);
    ~Webserv();
};

int msg_error(int status);

#endif
