#include "webserv.hpp"
#include "../src/response/Response.hpp"

/////////////////////////////////////
//      destructor constructor
/////////////////////////////////////
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

/////////////////////////////////////
//      getters and setters
/////////////////////////////////////
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
std::map<int, Client> &Webserv::get_Clients()
{
    return _clients;
}

//////////////////////////////////////////
//      member function                 //
//////////////////////////////////////////

int ft_exit(std::string a)
{
    perror(a.c_str());
    exit(1);
}

int Webserv::init_server()
{
    int optval = 1;
    int sockfd;
    int i = 0;
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
        // for solve problem (address already in use)
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
int g;
std::map<int, std::string> clit;

int Webserv::ft_accept(pollfd &tmp_fd)
{
    struct sockaddr_in cli_addr;
    socklen_t cli_addr_len;
    pollfd accepted;

    cli_addr_len = sizeof(cli_addr);
    accepted.fd = accept(tmp_fd.fd, (struct sockaddr *)&cli_addr, &cli_addr_len);
    std::cout << ":::::> " << accepted.fd << std::endl;
    if (accepted.fd == -1)
    {
        perror("accept error\n");
        return -1;
    }
    else
    {
        if (fcntl(accepted.fd, F_SETFL, O_NONBLOCK) < 0)
        {
            perror("fcntl error");
            exit(1);
        }
        accepted.events = POLLIN;
        Client *client = new Client(_servers[tmp_fd.fd]);

        client->plfd = accepted;
        client->global = g++;

        _vect.push_back(client);
        for (int i = 0; i < _vect.size(); i++)
            std::cout << _vect[i]->global << "|";
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
    _vect[j]->setReuqst(buf);
    _vect[j]->find_request_eof();
    // std::cout << _vect[j]->getReuqst() << std::endl;
    if (_vect[j]->getEof() == true)
    {
        tmp_fd.events = POLLOUT;
        std::cout << _vect[j]->getReuqst() << std::endl;
        // std::cout << "================================================================" << std::endl;
        Prasing_Request prs_reqst(_vect[j]->getReuqst());
        _vect[j]->setParsingRequest(prs_reqst);
        Response response(prs_reqst, _vect[j]->getConfiguration());
        _vect[j]->setResponse(response);
        _vect[j]->setMessage(_vect[j]->getResponse().get_respons(), 0);

        // std::cout << _clients[tmp_fd.fd].getMessage() << std::endl;
        // std::cout<<_clients[tmp_fd.fd].getConfiguration().getlisten()<<std::endl;
    }
    return 0;
}
int Webserv::ft_send(pollfd tmp_fd, int index)
{
    char buf[BUFFERSIZE];
    bzero(buf, BUFFERSIZE);
    sprintf(buf, "HTTP/1.1 200 OK\r\n"
                 "Content-Type: text/plain\r\n"
                 "Content-Length: 12\r\n"
                 "\r\n"
                 "hello world\n");
    int n = strlen(buf);
    send(tmp_fd.fd, buf, n, 0);
    // std::cout << "||||||" << n << "||" << _clients[tmp_fd.fd].getResponse().get_respons().size() << std::endl;
    // n = send(tmp_fd.fd, _clients[tmp_fd.fd].getMessage().c_str(), _clients[tmp_fd.fd].getMessage().size(), 0);
    // _clients[tmp_fd.fd].setMessage(_clients[tmp_fd.fd].getMessage(), n);
    // if (_clients[tmp_fd.fd].getMessage().empty())
    // {
    // close(tmp_fd.fd);
    _pollfd.erase(_pollfd.begin() + index);
    // _clients.erase(_clients.find(_pollfd[index].fd));
    // }
    return 0;
}

int Webserv::run_server()
{
    setup_poollfd();
    g = 0;
    while (Webserv::_true)
    {

        std::cout << "----------------\n";
        std::cout << std::endl;
        int v = poll(_pollfd.data(), _pollfd.size(), -1);

        if ((_pollfd[0].revents & POLLIN) && (_servers.find(_pollfd[0].fd) != _servers.end()))
            ft_accept(_pollfd[0]);
        for (int i = 1; i < _pollfd.size(); i++)
        {
            if ((_pollfd[i].revents & POLLIN))
            {
                for (int j = 0; j < _vect.size(); j++)
                {
                    if (_vect[j]->plfd.fd == _pollfd[i].fd)
                        ft_recv(_pollfd[i], j);
                }
            }
            if ((_pollfd[i].revents & POLLOUT))
            {

                for (int j = 0; j < _vect.size(); j++)
                {
                    if (_vect[j]->plfd.fd == _pollfd[i].fd)
                    {
                        //     ft_recv(_pollfd[i], j);

                        std::string msg;
                        msg += "HTTP/1.1 200 OK\r\n";
                        msg += "Content-Type: text/plain\r\n";
                        msg += "Content-Length: 12\r\n";
                        msg += "\r\n";
                        time_t tm = time(NULL);
                        if (tm % 2)
                            msg += "hello world\n";
                        else
                            msg += "waxch khadm\n";
                        // send(_pollfd[i].fd, msg.c_str(), msg.size(), 0);
                        // std::cout << "||||||" << n << "||" << _clients[tmp_fd.fd].getResponse().get_respons().size() << std::endl;
                        int n = send(_pollfd[i].fd, _vect[j]->getMessage().c_str(), _vect[j]->getMessage().size(), 0);
                        std::cout << _vect[j]->getMessage();
                        _vect[j]->setMessage(_vect[j]->getMessage(), n);
                        if (_vect[j]->getMessage().empty())
                        {
                            //     // std::cout << "\n\n\n==>" << _clients[i].global << "\n\n";

                            close(_pollfd[i].fd);
                            _pollfd.erase(_pollfd.begin() + i);
                            _vect.erase(_vect.begin() + j);

                            //     // if (_clients.find(_poll.[i].fd) != _clients.end())
                            //     //     ;
                            //     // _clients.erase(_cli.ts.find(_poll.[i].fd));
                            //     // clit.erase(clit.find(_pollfd[i].fd));

                            //     // std::cout << _pollfd.size() << "======================" << std::endl;

                            //     // i--;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

/////////////////////////////////////////////// configiration //////////////////////////////
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


