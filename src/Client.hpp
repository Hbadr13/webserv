#include <iostream>
#include <string>
#include <map>
#ifndef CLIENT_HPP
#define CLIENT_HPP
#include "Configfile/Configuration.hpp"

class Client
{
    private:
        Configuration _config;
        std::string _reuqst;
    public:
    std::string getReuqst();
    void setReuqst(std::string value);
    Client(Configuration &confi);
    Client();
    ~Client();
};

#endif
