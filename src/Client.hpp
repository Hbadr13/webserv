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
    std::map<std::string ,std::string> _mymap;
    std::string _Transfer_Encoding;
    Prasing_Request _parsing_reqst;
    std::string _content_Length;
    std::string _hostrqst;
    Configuration _config;
    std::string _message;
    std::string _headrs;
    std::string _reuqst;
    Response _response;
    std::string _body;
    int _readyToRecv;
    int _cont_legth;
    int _connecfd;
    int _sizedata;
    int global;
    int _eof;
public:
    
    pollfd plfd;
    //---->      Getters & Setters     <---\\.
    void setConfiguration(Configuration &conf);
    Prasing_Request &getParsingRequest();
    std::string &getTransfer_Encoding();
    Configuration &getConfiguration();
    std::string &getHostrqst();
    void setConnecfd(int fd);
    std::string &getReuqst();
    Response &getResponse();
    int &getReadyToRecv();
    int getConnecfd();
    int &getEof();
    std::string &getMessage();
    void setParsingRequest(Prasing_Request &prsrqst);
    void setTransfer_Encoding(std::string &value);
    void setMessage(std::string value, int size);
    void setReuqst(char *value , int n);
    void setHostrqst(std::string hostt);
    void setResponse(Response respse);
    void setReadyToRecv(int &value);
    
    //---->       Memeber Fuction      <---\\.
    int find_Transfer_Encoding();
    int find_content_length();
    int find_request_eof();
    
    //---->  Construction & Destructor <---\\.
    Client(Configuration &confi);
    ~Client();
    Client();
};

#endif
