#ifndef WEBSERV_HPP
#define WEBSERV_HPP

// #include "Configfile/Configuration.hpp"
#include "../src/request/Request.hpp"
//    define variables //
#define BUFFERSIZE 40000

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
#include <poll.h>
#include <fstream>
#include <stdlib.h>
#include "Client.hpp"
class Webserv
{
private:
    static const int _true = true;
    std::map<int, Configuration>    _servers;
    std::vector<Configuration>      _confgs;
    std::vector<Client *>           _clients;
    std::vector<pollfd>             _pollfd;

public:
    //---->      Getters & Setters     <---\\.
    std::map<int, Configuration>    &getServers();
    std::vector<Configuration>      &getConfgs();
    std::vector<Client*>            &getClients();
    std::vector<pollfd>             &getPollfd();

    //---->       Memeber Fuction      <---\\.
    int                             ft_send(pollfd &tmp_fd, int i, int j);
    int                             ft_recv(pollfd &tmp_fd,int i, int j);
    int                             ft_accept(pollfd &tmp_fd);
    int                             server_matching(int j);
    int                             setup_poollfd();
    int                             init_server();
    int                             run_server();

    //---->  Construction & Destructor <---\\.
    Webserv(char *path);
    ~Webserv();
    Webserv();
};
std::string cleaning_input(std::string str);

#endif
