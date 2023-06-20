#ifndef RESPONSE_HPP
#define RESPONSE_HPP

//    define variables //

// -------  cpp -----//
#include <iostream>

// ------    c   ----//
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>  /* See NOTES */
#include <netinet/in.h> // for type (struct sockaddr_in)
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <map>
#include <sstream>
#include <ctime>
#include <fstream>
#include <filesystem>
#include <dirent.h>
#include <iostream>
#include <string>
#include "../request/Request.hpp"
#include "sys/wait.h"
class Response
{
private:
    int                                     status;
    std ::map<std::string, std::string>     mymap;
    std ::map<int , std::string>            mymap_erorr;
    std::string                             respons;

public:
    Response(Request rq, Configuration conf_serv);
    Response();
    ~Response(); 
    int                                     run_cgi(Location &location, Request &requst, Configuration &conf_serv,std::string psth);
    std ::string                            get_respons();
};
std::string                                 ft_read(std::string name);
std::string                                 int_to_string(int numb);
std ::string                                Content_type(std ::string root);

#endif
