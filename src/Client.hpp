#include <iostream>
#include <string>
#include <string.h>
#include <map>
#ifndef CLIENT_HPP
#define CLIENT_HPP
#include "Configfile/Configuration.hpp"
#include "../src/request/Prasing_Request.hpp"
#include "response/Response.hpp"
#include <poll.h>


class Client
{
private:
    Prasing_Request _parsing_reqst;
    std::string _content_Length;
    Configuration _config;
    std::string _reuqst;
    std::string _headrs;
    int _readyToRecv;
    std::string _Transfer_Encoding;
    Response _response;
    std::string _message;
    std::string _body;
    int _cont_legth;
    int _eof;
    int _sizedata;
public:
    pollfd plfd;
    int global;
    Prasing_Request &getParsingRequest();
    Configuration &getConfiguration();
    Response &getResponse();
    std::string &getReuqst();
    int &getReadyToRecv();
    int &getEof();
    std::string &getTransfer_Encoding();
    void setTransfer_Encoding(std::string &value);
    std::string &getMessage();

    void setParsingRequest(Prasing_Request &prsrqst);
    void setResponse(Response respse);
    void setReuqst(char *value , int n);
    void setReadyToRecv(int &value);
    void setMessage(std::string value, int size);
    int find_content_length();
    int find_request_eof();
    int find_Transfer_Encoding();
    Client(Configuration &confi);
    ~Client();
    Client();
};

#endif
