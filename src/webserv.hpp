#ifndef WEBSERV_HPP
#define WEBSERV_HPP

// #include "Configfile/Configuration.hpp"
#include "../src/request/Prasing_Request.hpp"
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
    std::vector<pollfd> _pollfd;
    std::vector<Configuration> _confgs;
    std::map<int, Configuration> _servers;
    std::vector<Client *> _clients;

public:
    //---->      Getters & Setters     <---\\.
    std::vector<pollfd> &getPollfd();
    std::vector<Configuration> &getConfgs();
    std::map<int, Configuration> &getServers();
    std::vector<Client*> &getClients();

    //---->       Memeber Fuction      <---\\.
    int setup_poollfd();
    int init_server();
    int run_server();
    int ft_accept(pollfd &tmp_fd);
    int ft_recv(pollfd &tmp_fd,int i, int j);
    int ft_send(pollfd &tmp_fd, int i, int j);
    int server_matching(int j);

    //---->  Construction & Destructor <---\\.
    Webserv(char *path);
    Webserv();
    ~Webserv();
};
std::string cleaning_input(std::string str);
int msg_error(int status);

#endif
