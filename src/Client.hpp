#include <iostream>
#include <string>
#include <string.h>
#include <map>
#ifndef CLIENT_HPP
#define CLIENT_HPP
#include "Configfile/Configuration.hpp"
#include "../src/request/Request.hpp"
#include "response/Response.hpp"
#include <poll.h>


class Client
{ 
private:
    std::map<std::string ,std::string>  _mymap;
    std::string                         _Transfer_Encoding;
    Request                             _parsing_reqst;
    std::string                         _content_Length;
    std::string                         _hostrqst;
    Configuration                       _config;
    std::string                         _message;
    std::string                         _headrs;
    std::string                         _reuqst;
    Response                            _response;
    std::string                         _body;
    int                                 _readyToRecv;
    int                                 _cont_legth;
    int                                 _connecfd;
    // int                                 _sizedata;
    pollfd                              _plfd;
public:
    
    int                                 _eof;
    //---->      Getters & Setters     <---\\.
    Request                             &getParsingRequest();
    Configuration                       &getConfiguration();
    std::string                         &getTransfer_Encoding();
    std::string                         &getHostrqst();
    std::string                         &getMessage(); 
    std::string                         &getReuqst();
    int                                 &getReadyToRecv();
    Response                            &getResponse();
    int                                 getConnecfd();
    pollfd                              &getPlfd();
    int                                 &getEof();
    void                                setParsingRequest(Request &prsrqst);
    void                                setTransfer_Encoding(std::string &value);
    void                                setMessage(std::string value, int size);
    void                                setConfiguration(Configuration &conf);
    void                                setReuqst(char *value , int n);
    void                                setHostrqst(std::string hostt);
    void                                setResponse(Response respse);
    void                                setReadyToRecv(int &value);
    void                                setPolfd(pollfd plfd);
    void                                setConnecfd(int fd);
    
    //---->       Memeber Fuction      <---\\.
    int                                 find_Transfer_Encoding();
    int                                 find_content_length();
    int                                 find_request_eof();
    int                                 find_Host();
    
    //---->  Construction & Destructor <---\\.
    Client(Configuration &confi)        ;
    ~Client()                           ;
    Client()                            ;
};

#endif
