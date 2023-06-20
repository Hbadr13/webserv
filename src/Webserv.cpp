#include "Webserv.hpp"
#include "../src/response/Response.hpp"

Webserv::Webserv()
{
}

Webserv::~Webserv()
{
    size_t i = 0;
    while (i < _clients.size())
    {
        if (_clients[i])
            delete _clients[i];
        i++;
    }
}

Webserv::Webserv(char *path)
{
    std::vector<std::string> config;
    std::vector<std::string> cnf;
    std::string line_s;
    std::string line;
    int flag = 0;
    size_t i = 0;

    std::ifstream file(path);
    if (file.is_open() == 0)
    {
        std::cout << "ERROR: Configiuration File Note Founde" << std::endl;
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

std::vector<struct pollfd> &Webserv::getPollfd()
{
    return _pollfd;
    ;
}
std::vector<Configuration> &Webserv::getConfgs()
{
    return _confgs;
}
std::map<int, Configuration> &Webserv::getServers()
{
    return _servers;
}
std::vector<Client *> &Webserv::getClients()
{
    return _clients;
}


int Webserv::init_server()
{
    int optval = 1;
    int sockfd;
    size_t i;

    i = 0;
    while (i < _confgs.size())
    {
        std::cout << _confgs[i].getlisten() << std::endl;
        struct sockaddr_in serv_addr;
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd == -1)
        {
            perror("socket:");
            return 1;
        }
        if ((setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int))) == -1)
        {
            perror("socket:");
            return 1;
        }
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(_confgs[i].getlisten());
        if (bind(sockfd, (struct sockaddr *)(&serv_addr), sizeof(serv_addr)) == -1)
            ;
        if (listen(sockfd, SOMAXCONN) == -1)
        {
            perror("listen:");
            return 1;
        }
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
        fd.events = POLLIN | POLLOUT;
        _pollfd.push_back(fd);
        it++;
    }
    return 0;
}

int Webserv::server_matching(int j)
{
    std::map<int, Configuration>::iterator  it;
    int                                     flag;
    int                                     num;

    it = _servers.begin();
    flag = true;
    num = 0;
    while (it != _servers.end())
    {
        if (it->second.getlisten() == _servers[_clients[j]->getConnecfd()].getlisten())
            num++;
        it++;
    }
    if (num >= 2)
    {
        it = _servers.begin();
        while (it != _servers.end())
        {
            if (it->second.getlisten() == _servers[_clients[j]->getConnecfd()].getlisten())
            {
                if (it->second.gethost() == _clients[j]->getHostrqst())
                {
                    _clients[j]->setConfiguration(it->second);
                    flag = false;
                    break;
                }
            }
            it++;
        }
    }
    if (flag)
        _clients[j]->setConfiguration(_servers[_clients[j]->getConnecfd()]);
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
        return 1;
    }
    else
    {
        accepted.events = POLLIN;
        Client *client = new Client();
        client->setPolfd(accepted);
        client->setConnecfd(tmp_fd.fd);
        _clients.push_back(client);
        _pollfd.push_back(accepted);
    }
    return 0;
}

int Webserv::ft_recv(pollfd &tmp_fd, int i, int j)
{
    char buf[BUFFERSIZE];
    bzero(buf, BUFFERSIZE);
    int sizeofdata;
    sizeofdata = recv(tmp_fd.fd, buf, BUFFERSIZE, 0);
    if (sizeofdata < 0)
    {
        std::cout << "Error: unable to receive data from client FD " << tmp_fd.fd << "\n";
        close(tmp_fd.fd);
        delete _clients[j];
        _pollfd.erase(_pollfd.begin() + i);
        _clients.erase(_clients.begin() + j);
        return 1;
    }
    if (sizeofdata == 0)
    {
        std::cout << "client " << tmp_fd.fd << " closed connection" << std::endl;
        close(tmp_fd.fd);
        delete _clients[j];
        _pollfd.erase(_pollfd.begin() + i);
        _clients.erase(_clients.begin() + j);
        return 1;
    }
    _clients[j]->setReuqst(buf, sizeofdata);
    _clients[j]->find_request_eof();
    if (_clients[j]->getEof() == true)
    {
        tmp_fd.events = POLLOUT;
        _clients[j]->_eof = 0;
        server_matching(j);
        Request prs_reqst(_clients[j]->getReuqst(),_clients[j]->getConfiguration());
        _clients[j]->setParsingRequest(prs_reqst);
        Response response(prs_reqst, _clients[j]->getConfiguration());
        _clients[j]->setResponse(response);
        _clients[j]->setMessage(_clients[j]->getResponse().get_respons(), 0);
    }
    return 0;
}

int Webserv::ft_send(pollfd &tmp_fd, int i, int j)
{
    int sizeofdata;

    sizeofdata = send(tmp_fd.fd, _clients[j]->getMessage().c_str(), _clients[j]->getMessage().size(), 0);
    if (sizeofdata < 0)
    {
        std::cout << "Error: unable to send data to client FD " << tmp_fd.fd << "\n";
        close(tmp_fd.fd);
        delete _clients[j];
        _pollfd.erase(_pollfd.begin() + i);
        _clients.erase(_clients.begin() + j);
        return 1;
    }
    _clients[j]->setMessage(_clients[j]->getMessage(), sizeofdata);
    if (_clients[j]->getMessage().empty())
    {
        close(tmp_fd.fd);
        delete _clients[j];
        _pollfd.erase(_pollfd.begin() + i);
        _clients.erase(_clients.begin() + j);
    }
    return 0;
}

int Webserv::run_server()
{
    size_t i;
    int return_poll;
    setup_poollfd();
    while (Webserv::_true)
    {
        i = 0;
        return_poll = poll(_pollfd.data(), _pollfd.size(), -1);
        while (i < _servers.size())
        {
            if ((_pollfd[i].revents & POLLIN) && (_servers.find(_pollfd[i].fd) != _servers.end()))
                ft_accept(_pollfd[i]);
            i++;
        }
        while (i < _pollfd.size())
        {
            if ((_pollfd[i].revents & POLLIN))
            {
                for (size_t j = 0; j < _clients.size(); j++)
                {
                    if (_clients[j]->getPlfd().fd == _pollfd[i].fd)
                        ft_recv(_pollfd[i], i, j);
                }
            }
            if ((_pollfd[i].revents & POLLOUT))
            {
                for (size_t j = 0; j < _clients.size(); j++)
                {
                    if (_clients[j]->getPlfd().fd == _pollfd[i].fd)
                        ft_send(_pollfd[i], i, j);
                }
            }
            i++;
        }
    }
    return 0;
}
