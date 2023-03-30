#include "Client.hpp"

Client::Client()
{
}
Client::~Client()
{
    _content_Length = "";
    _readyToRecv = true;
    // _config.~Configuration();
    _headrs = "";
    _reuqst = "";
    _body = "";
}
Response &Client::getResponse()
{
    return _response;
}
void Client::setResponse(Response respse)
{
    _response = respse;
}
int &Client::getReadyToRecv()
{
    return _readyToRecv;
}
void Client::setReadyToRecv(int &value)
{
    _readyToRecv = value;
}
Client::Client(Configuration &confi)
{
    _content_Length = "";
    _readyToRecv = true;
    _config = confi;
    _headrs = "";
    _reuqst = "";
    _body = "";
}

Prasing_Request &Client::getParsingRequest()
{
    return _parsing_reqst;
}
std::string &Client::getMessage()
{
    return _message;
}
void Client::setMessage(std::string value, int size)
{
   if(_message.empty())
    exit(1);
    _message = value.substr(size, value.length() - size);
    std::cout<<_message<<std::endl;
}

void Client::setParsingRequest(Prasing_Request &prsrqst)
{
    _parsing_reqst = prsrqst;
}
std::string &Client::getReuqst()
{
    return _reuqst;
}
void Client::setReuqst(std::string value)
{
    _reuqst.append(value);
}

int &Client::getEof()
{
    return _eof;
}
Configuration &Client::getConfiguration()
{
    return _config;
}
int Client::find_content_length()
{
    if (_reuqst.find("Content-Length") == std::string::npos)
        return 0;
    int start = _reuqst.find("Content-Length") + strlen("Content-Length: ");
    int i = start;
    while (i < _reuqst.size() - 1)
    {
        if (_reuqst[i] == '\r' && _reuqst[i + 1] == '\n')
        {
            _content_Length = _reuqst.substr(start, i - start);
            return 1;
        }
        i++;
    }
    return 0;
}

int Client::find_request_eof()
{
    std::string farstline;
    if (_readyToRecv)
    {
        if (find_content_length())
        {
            _readyToRecv = false;
            _cont_legth = atoi(_content_Length.c_str());
        }
    }
    if (_reuqst.find("\r\n\r\n") != std::string::npos && _headrs.empty())
    {
        _headrs = _reuqst.substr(0, _reuqst.find("\r\n\r\n")) + "\r\n\r\n";
        if (_content_Length.empty())
            _eof = true;
    }
    if (_readyToRecv == false)
    {
        if (_reuqst.size() == _cont_legth + _headrs.size())
            _eof = true;
    }
    return 0;
}
