#include <iostream>
#include <string>
#include <map>
#ifndef CLIENT_HPP
#define CLIENT_HPP
#include "Configfile/Configuration.hpp"

class Client
{
private:
    int _eof;
    int _readyToRecv;
    Configuration _config;
    std::string _reuqst;

public:
    std::string getReuqst();
    void setReuqst(std::string value);
    int getReadyToRecv();
    int find_request_eof();
    void setReadyToRecv(int value);
    int getEof();
    Client(Configuration &confi);
    Client();
    ~Client();
};

#endif
