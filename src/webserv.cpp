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
    this->port = 2012;
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
        if(line.empty())
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
    int i =0 ;
    int flag = 0;
    while (i < config.size())
    {
        cnf.push_back(config[i]);
        if((!config[i].compare("server") && flag == 1))
        {
            cnf.pop_back();
            Configuration c(cnf);
            this->confgs.push_back(c);
            flag = 0;
            cnf.clear();
            continue;
        }
        else if(i == config.size() - 1)
        {
            Configuration c(cnf);
            this->confgs.push_back(c);
            cnf.clear();
            break;
        }
        if(!config[i].compare("server"))
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
std::vector<Configuration> Webserv::getConfs()
{
    return this->confgs;
}

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
    while (i < this->confgs.size())
    {
        std::cout << this->confgs[i].getlisten() << std::endl;
        struct sockaddr_in serv_addr;
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        // for solve problem (address already in use)
        if ((setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int))) == -1)
        {
            perror("socket error\n");
            return -1;
        }
        if (sockfd == -1)
            ft_exit("0");
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(this->confgs[i].getlisten());
        serv_addr.sin_addr.s_addr = INADDR_ANY;

        // bind the socket to localhost port 5500
        if (bind(sockfd, (struct sockaddr *)(&serv_addr), sizeof(serv_addr)) == -1)
            ft_exit("1");
        if (listen(sockfd, 5) == -1)
            ft_exit("2");
        std::cout<<"{"<<this->confgs[i].getroot()<<std::endl;
        this->server.insert(std::make_pair(sockfd, this->confgs[i]));
        this->max_fd = sockfd;
        i++;
    }

    return 0;
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

int Webserv::run_server()
{
    // std::string response = ft_read("www/index.html");
    char client_msg[4096] = "";
    int client_socket;

    FD_ZERO(&this->stes_read);
    for (std::map<int, Configuration>::iterator it = this->server.begin(); it != this->server.end(); it++)
        FD_SET(it->first, &this->stes_read);

    // FD_ZERO(&this->stes_write);
    // FD_SET(this->sockfd, &this->stes_write);
    // this->max_fd = this->sockfd;

    while (true)
    {
        printf("------------> wait ....\n");
        fd_set tempfds = this->stes_read;
        int fd_select = select(this->max_fd + 1, &tempfds, NULL, NULL, NULL);
        for (std::map<int, Configuration>::iterator it = this->server.begin(); it != this->server.end(); it++)
        {

            if (FD_ISSET(it->first, &tempfds))
            {
                // if (fd == this->sockfd)
                // {
                    client_socket = accept(it->first, NULL, NULL);
                    // FD_SET(client_socket, &this->stes_read);
                    // FD_SET(client_socket, &this->stes_write);
                    // if (client_socket > this->max_fd)
                    //     this->max_fd = client_socket;
                // }
                // else
                // {
                     it->second.getlocations();
                    recv(client_socket, client_msg, 4095, 0);

                    std::cout << "=============================\n\n"
                              << std::endl;
                              Prasing_Request as(client_msg);
                              
                              Response  aj(as,it->second);
                               std :: string respons = aj.get_respons();

                    // for (int fd2 = 0; fd2 <= this->max_fd; fd2++)
                    // {
                    //     if (FD_ISSET(fd2, &this->stes_write))
                    //     {
                            send(client_socket, respons.c_str(), respons.length(), 0);
                    //         printf("====> %d | %d\n", fd, fd2);
                    //         close(fd2);
                    //         FD_CLR(fd2, &this->stes_write);
                    //     }
                    // }
                    close(client_socket);
                    // FD_CLR(fd, &this->stes_read);
                // }
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
        if(!str[i])
            break;
        i++;
    }
    return dst;
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
        if(!mot.empty())
            vect.push_back(mot);
        i++;
    }
    return vect;
}
