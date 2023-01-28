#include "../include/webserv.hpp"


/////////////////////////////////////
//      destructor constructor 
/////////////////////////////////////
Webserv::Webserv()
{
}
Webserv::Webserv(int prt, int backlg)
{
    this->port = prt;
    this->backlog = backlg;
}
Webserv::~Webserv()
{
}

/////////////////////////////////////
//      getters and setters 
/////////////////////////////////////
int Webserv::getport()
{
    return this->port;
}
void Webserv::setport(int prt)
{
    this->port = prt;
}

int Webserv::getsockfd()
{
    return this->sockfd;
}
void Webserv::setsockfd(int sckfd)
{
    this->sockfd = sckfd;
}
int Webserv::getbacklog()
{
    return this->backlog;
}
void Webserv::setbacklog(int backlog)
{
    this->backlog = backlog;
}


//////////////////////////////////////////
//      member function
////////////////////////////////////////
int Webserv::init_server()
{
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
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

int Webserv::run_server()
{
    // int var = sizeof(this->serv_addr);
    // std::cout << sizeof(socklen_t);
    // int fd_client;
    // while (true)
    // {
    char client_msg[4096] = "";
    int client_socket = accept(this->sockfd, NULL, NULL);
    recv(client_socket, client_msg, 4095, 0);

    int fd = open("file", O_RDONLY);
    char str[4096] ="";
    // printf("%s\n", str);
    read(fd, str, 2000);
    send(client_socket, str, sizeof(str), 0);
    // // close(this->sockfd);
    // // std::cout << "connected\n";
    // }
    return 0;
}