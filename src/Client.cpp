#include "Client.hpp"

Client::Client()
{
}
Client::~Client()
{
}

int Client::getReadyToRecv()
{
    return _readyToRecv;
}
void Client::setReadyToRecv(int value)
{
    _readyToRecv = value;
}
Client::Client(Configuration &confi)
{
    _reuqst = "";
    _readyToRecv = false;
    _config = confi;
}
std::string Client::getReuqst()
{
    return _reuqst;
}
void Client::setReuqst(std::string value)
{
    _reuqst.append(value);
}

int Client::getEof()
{
    return _eof;
}
int Client::find_request_eof()
{
    std::string farstline;
    farstline = _reuqst.substr(0, _reuqst.find("\n\r"));
    std::vector<std::string> vect = split_string(farstline, ' ');

    if (_reuqst.find("\r\n\r\n") != std::string::npos)
        _eof = true;

    return 0;
}