#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string>
#include <vector>
#include <stack>
#include <map>

#include <string>
#include <fcntl.h>
#include <iostream>
#include <fstream>
#include <sys/wait.h>
struct sockaddr_in serv_addr;
int optval;
int sockfd;
fd_set readd;
int fd_max;
int port;
int ft_exit(std::string a)
{
    perror(a.c_str());
    exit(1);
}
std::string ft_read(std::string name)
{
    std::string line_s;
    std::string line;

    std::ifstream file(name.c_str());
    if (file.is_open() == 0)
    {
        std::cout << "error: configiuration file note founde\n";
        exit(1);
    }
    while (getline(file, line))
    {
        line.append("\n");
        line_s += line;
    }
    return line_s;
}
std::vector<std::string> split_string(std::string str, char c)
{
    std::vector<std::string> vect;
    std::string mot;
    int start;
    int i;
    i = 0;
    while (str[i])
    {
        while (str[i] && str[i] == c)
            i++;
        start = i;
        while (str[i] && str[i] != c)
            i++;
        mot = str.substr(start, i - start);
        if (!mot.empty())
            vect.push_back(mot);
        i++;
    }
    return vect;
}
int ft_init(int port)
{
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if ((setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int))) == -1)
        ft_exit("exit");
    if (sockfd == -1)
        ft_exit("0");
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sockfd, (struct sockaddr *)(&serv_addr), sizeof(serv_addr)) == -1)
        ft_exit("1");
    if (listen(sockfd, 5) == -1)
        ft_exit("2");
    FD_ZERO(&readd);
    FD_SET(sockfd, &readd);
    fd_max = sockfd;
    return sockfd;
}

std::string ft_cgi(std::string re, char **envp)
{
    char **av;
    av = (char **)malloc(sizeof(char *) * 3);
    std::vector<std::string> requst = split_string(re, ' ');
    // std::string path = "www/cgi-bin/test.py";
    std::string path = requst[1];
    std::cout << path << std::endl;
    if (path.length() <= 3)
        ft_exit("\n\nlength path");

    if (path.compare(path.length() - 3, 3, ".py"))
        ft_exit("\n\n.py");
    if (path.compare(path.length() - 3, 3, ".py"))
    {
        av[0] = strdup("/usr/bin/python3");
        av[1] = strdup(path.c_str());
        av[2] = NULL;
    }
    int fd_execute = open(path.c_str(), O_RDONLY);
    if (fd_execute < 0)
        ft_exit("\n\nopen1");
    int fd = open("trash", O_WRONLY | O_TRUNC);
    if (fd < 0)
        ft_exit("\n\nopen2");
    int pid = fork();
    if (pid == 0)
    {
        // dup2(fd_execute, 0);
        dup2(fd, 1);
        std::cout << "hello\n";
        execve(av[0], av, envp);
        exit(1);
    }
    else
    {
        waitpid(pid, NULL, 0);
        close(fd);
        close(fd_execute);
    }
    std::string respons;
    respons = "HTTP/1.1 200 OK\n";
    respons += ft_read("trash");
    return respons;
}
int main(int ac, char **av, char **envp)
{

    port = atoi(av[1]);
    ft_init(port);
    while (1)
    {
        fd_set tmp_fds = readd;
        if (select(fd_max + 1, &tmp_fds, NULL, NULL, NULL) < 0)
            ft_exit("select");
        if (FD_ISSET(sockfd, &tmp_fds))
        {
            struct sockaddr_in cliaddr;
            socklen_t clilen = sizeof(cliaddr);
            int newfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);
            char buffer[1024];
            if (read(newfd, buffer, 1024) < 0)
                ft_exit("read");
            printf("from: port\n");
            std::string response = ft_cgi(buffer, envp);
            write(1, response.c_str(), response.length());
            if (write(newfd, response.c_str(), strlen(response.c_str())) < 0)
                ft_exit("write");
            close(newfd);
        }
    }
}
