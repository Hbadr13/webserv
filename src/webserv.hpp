#ifndef WEBSERV_HPP
#define WEBSERV_HPP
#include "Configfile/Configuration.hpp"
#include "../src/request/Prasing_Request.hpp"
//    define variables //

// -------  cpp -----//
#include <iostream>
#include <fstream>
#include <string>
// ------    c   ----//
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>  /* See NOTES */
#include <netinet/in.h> // for type (struct sockaddr_in)
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sstream>
#include <stdlib.h>
class Webserv
{
private:
public:
    std::vector<Configuration> confgs;
    std::map<int , Configuration> server;
    int port;
    int sockfd;
    int backlog; // a maximum pending connections for master socket
    struct sockaddr_in serv_addr;

    //  SELECT
    fd_set stes_write;
    fd_set stes_read;
    int max_fd;
    //----> getters and setters <--\\.
    int getport();
    void setport(int prt);
    int getsockfd();
    void setsockfd(int sckfd);
    int getbacklog();
    void setbacklog(int backlog);
    std::vector<Configuration> getConfs();
    //---->  memeber fuction <---\\.
    int init_server();
    int run_server();
    Webserv();
    Webserv(char *path);
    ~Webserv();
};
std::string cleaning_input(std::string str);
std::vector<std::string> split_string(std::string str, char c);
int msg_error(int status);
std::string ft_read(std::string name);

#endif
