#include "src/webserv.hpp"

#include "src/Configfile/Configuration.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
        exit(1);
/*
pollfd fd[20];
int fd1;
int fd2;
// server
fd[0].fd = fd1;
fd[0].events = POLLIN;

fd[1].fd = fd2;
fd[1].events = POLLIN;

// fd[1].
// clients
int fd_cl1;
fd[2].fd = fd_cl1;
fd[2].events = POLLIN;
poll(fd, 3, -1);
int i = 0;
while (i < 3)
{
    if (fd[i].revents == POLLIN && fd[i] == serv)
        accept(fd[i]);
    if (fd[i].revents == POLLIN && fd[i] == Client)
    {
        read(fd[i]);
        fd[i].events = POLLOUT;
    }

    if (fd[i].revents == POLLOUT && fd[i] == client)
        write(fd[i]);
}



*/

    // Configuration conf((std::string)argv[1]);
    // Location location(conf, "/");
    // std::cout << location.getallow_methods()[0];
    // return 0;
    // std::vector<Configuration> confs;
    // confs.push_back(conf);
    Webserv myserver(argv[1]);
    if (-1 == myserver.init_server())
        return 1;
    myserver.run_server();

    return 0;
}
