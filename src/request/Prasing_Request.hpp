#ifndef PRASING_REQUEST_HPP
#define PRASING_REQUEST_HPP
#include "../Configfile/Configuration.hpp"
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <map>

class Prasing_Request
{
private:
    std::string                         methode;
    std::string                         url;
    std::string                         budy_url;
    int                                 status;
    long long                           _limit_pody;
    std ::map<std::string, std::string> mymap;

public:

    Prasing_Request(std::string hedr , Configuration &conf_serv);
    Prasing_Request();
    ~Prasing_Request();

    std::map<std::string,std::string>   get_mymap();
    std :: string                       get_budy_url();
    std :: string                       get_url();
    std::string                         get_method();
    int                                 get_status();
    
    void                                prasing_body(std :: string body1,std :: string body2);
    int                                 check_first_line(std::string first_line);
    void                                prasing_headr(std ::string headrs);
};
std::pair<Location, std::string> find_location(std::string url, Configuration conf_serv);
#endif
