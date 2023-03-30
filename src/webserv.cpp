#include "webserv.hpp"
#include "../src/response/Response.hpp"

Webserv::Webserv()
{
}

Webserv::Webserv(char *path)
{
    std::vector<std::string> config;
    std::string line_s;
    std::string line;

    std::ifstream file(path);
    if (file.is_open() == 0)
    {
        std::cout << "error: configiuration file  : file note founde\n";
        exit(1);
    }
    while (getline(file, line))
    {
        if (line.empty())
            continue;
        line.append("\t");
        std::replace(line.begin(), line.end(), '\t', ' ');
        if (line.find("#") != std::string::npos)
            line.erase(line.find("#"), line.length());
        line_s += line;
    }
    line_s = cleaning_input(line_s);
    config = split_string(line_s, ' ');
    std::vector<std::string> cnf;
    int i = 0;
    int flag = 0;
    while (i < config.size())
    {
        cnf.push_back(config[i]);
        if ((!config[i].compare("server") && flag == 1))
        {
            cnf.pop_back();
            Configuration c(cnf);
            _confgs.push_back(c);
            flag = 0;
            cnf.clear();
            continue;
        }
        else if (i == config.size() - 1)
        {
            Configuration c(cnf);

            _confgs.push_back(c);
            cnf.clear();
            break;
        }
        if (!config[i].compare("server"))
            flag = 1;
        i++;
    }

}
Webserv::~Webserv()
{

}
std::vector<struct pollfd> &Webserv::get_Pollfd()
{
    return _pollfd;
    ;
}
std::vector<Configuration> &Webserv::get_Confgs()
{
    return _confgs;
}
std::map<int, Configuration> &Webserv::get_Servers()
{
    return _servers;
}
std::vector<Client *> &Webserv::get_Clients()
{
    return _clients;
}

int ft_exit(std::string a)
{
    perror(a.c_str());
    exit(1);
}

int Webserv::init_server()
{
    int optval = 1;
    int sockfd;
    int i;

    i = 0;
    while (i < _confgs.size())
    {
        std::cout << _confgs[i].getlisten() << std::endl;
        struct sockaddr_in serv_addr;
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd == -1)
            ft_exit("0");
        if (fcntl(sockfd, F_SETFL, O_NONBLOCK) < 0)
        {
            perror("fcntl error");
            exit(1);
        }
        if ((setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int))) == -1)
        {
            perror("socket error\n");
            return -1;
        }
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(_confgs[i].getlisten());
        serv_addr.sin_addr.s_addr = INADDR_ANY;

        // bind the socket to localhost port 5500
        if (bind(sockfd, (struct sockaddr *)(&serv_addr), sizeof(serv_addr)) == -1)
            ft_exit("1");
        if (listen(sockfd, 5) == -1)
            ft_exit("2");
        _servers.insert(std::make_pair(sockfd, _confgs[i]));
        i++;
    }
    return 0;
}

int Webserv::setup_poollfd()
{
    std::map<int, Configuration>::iterator it = _servers.begin();

    while (it != _servers.end())
    {
        pollfd fd;
        fd.fd = it->first;
        fd.events = POLLIN | POLLOUT | POLLHUP;
        _pollfd.push_back(fd);
        it++;
    }
    return 0;
}

int Webserv::ft_accept(pollfd &tmp_fd)
{
    struct sockaddr_in cli_addr;
    socklen_t cli_addr_len;
    pollfd accepted;

    cli_addr_len = sizeof(cli_addr);
    accepted.fd = accept(tmp_fd.fd, (struct sockaddr *)&cli_addr, &cli_addr_len);
    if (accepted.fd == -1)
    {
        std::cout << "I can't handling this connection from port: " << _servers[tmp_fd.fd].getlisten() << std::endl;
        return -1;
    }
    else
    {
        if (fcntl(accepted.fd, F_SETFL, O_NONBLOCK) < 0)
        {
            perror("fcntl error");
            return -1;
        }
        accepted.events = POLLIN;
        Client *client = new Client(_servers[tmp_fd.fd]);
        client->plfd = accepted;
        _clients.push_back(client);
        std::cout << std::endl;
        _pollfd.push_back(accepted);
    }
    return 0;
}

int Webserv::ft_recv(pollfd &tmp_fd, int j)
{
    char buf[BUFFERSIZE];
    bzero(buf, BUFFERSIZE);
    int n = recv(tmp_fd.fd, buf, BUFFERSIZE, 0);
    if (n == 0)
    {
        printf("client %d closed connection\n", tmp_fd.fd);
        close(tmp_fd.fd);
        tmp_fd.fd = -1;
        return 1;
    }
    _clients[j]->setReuqst(buf);
    _clients[j]->find_request_eof();
    if (_clients[j]->getEof() == true)
    {
        tmp_fd.events = POLLOUT;
        // std::cout << _clients[j]->getReuqst() << std::endl;
        Prasing_Request prs_reqst(_clients[j]->getReuqst());
        _clients[j]->setParsingRequest(prs_reqst);
        Response response(prs_reqst, _clients[j]->getConfiguration());
        _clients[j]->setResponse(response);
        _clients[j]->setMessage(_clients[j]->getResponse().get_respons(), 0);
    }
    return 0;
}
int Webserv::ft_send(pollfd &tmp_fd, int i, int j)
{
    int n = send(tmp_fd.fd, _clients[j]->getMessage().c_str(), _clients[j]->getMessage().size(), 0);
        std::cout<<"----------1\n";
    std::cout<<"----------2\n";
    _clients[j]->setMessage(_clients[j]->getMessage(), n);
    if (_clients[j]->getMessage().empty())
    {
        close(tmp_fd.fd);
        _pollfd.erase(_pollfd.begin() + i);
        _clients.erase(_clients.begin() + j);
    }
    return 0;
}

int Webserv::run_server()
{
    int i; 
    int return_poll;
    setup_poollfd();
    while (Webserv::_true)
    {
        i = 0;
        return_poll = poll(_pollfd.data(), _pollfd.size(), -1);
        while(i < _servers.size())
        {
            if ((_pollfd[i].revents & POLLIN) && (_servers.find(_pollfd[i].fd) != _servers.end()))
                ft_accept(_pollfd[i]);
            i++;
        }
        while (i < _pollfd.size())
        {
            if ((_pollfd[i].revents & POLLIN))
            {
                for (int j = 0; j < _clients.size(); j++)
                {
                    if (_clients[j]->plfd.fd == _pollfd[i].fd)
                        ft_recv(_pollfd[i], j);
                }
            }
            if ((_pollfd[i].revents & POLLOUT))
            {
                for (int j = 0; j < _clients.size(); j++)
                {
                    if (_clients[j]->plfd.fd == _pollfd[i].fd)
                        ft_send(_pollfd[i], i, j);
                }
            }
            i++; 
        }
    }
    return 0;
}

std::string cleaning_input(std::string str)
{
    std::string dst;
    int start;
    int i = 0;
    while (str[i])
    {
        start = i;
        while (str[i] && str[i] != ';' && str[i] != '{' && str[i] != '}')
            i++;
        dst += str.substr(start, i - start);
        dst += " ";
        dst += str[i];
        dst += " ";
        if (!str[i])
            break;
        i++;
    }
    return dst;
}
