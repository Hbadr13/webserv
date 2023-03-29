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
    std::map<int, Client *> moch;
    std::vector<pollfd> &get_Pollfd();
    std::vector<Configuration> &get_Confgs();
    std::map<int, Configuration> &get_Servers();
    std::vector<Client*> &get_Clients();
    //---->  memeber  fuction <---\\.
    int setup_poollfd();
    int init_server();
    int run_server();
    int ft_accept(pollfd &tmp_fd);
    int ft_recv(pollfd &tmp_fd, int j);
    int ft_send(pollfd &tmp_fd, int i, int j);

    static int server_run()
    {
        return true;
    }
    Webserv();
    Webserv(char *path);
    ~Webserv();
};
std::string cleaning_input(std::string str);
int msg_error(int status);

#endif
