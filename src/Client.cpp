#include "Client.hpp"

Client::Client()
{
}

int Client::getConnecfd()
{
    return _connecfd;
}
void Client::setConnecfd(int fd)
{
    _connecfd = fd;
}

Client::~Client()
{
    _content_Length.clear();
    _eof = false;
    _readyToRecv = true;
    _headrs.clear();
    _reuqst.clear();
    _body.clear();
}
Client::Client(Configuration &confi)
{
    _content_Length.clear();
    _readyToRecv = true;
    _eof = false;
    _config = confi;
    _headrs.clear();
    _reuqst.clear();
    _body.clear();
}
void Client::setConfiguration(Configuration &conf)
{
    _config = conf;
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
pollfd &Client::getPlfd()
{
    return _plfd;
}
void Client::setPolfd(pollfd plfd)
{
    _plfd = plfd;
}
std::string &Client::getTransfer_Encoding()
{
    return _Transfer_Encoding;
}
void Client::setTransfer_Encoding(std::string &value)
{
    _Transfer_Encoding = value;
}
Prasing_Request &Client::getParsingRequest()
{
    return _parsing_reqst;
}
std::string &Client::getMessage()
{
    return _message;
}
std::string &Client::getHostrqst()
{
    return _hostrqst;
}
void Client::setHostrqst(std::string hostt)
{
    _hostrqst = hostt;
}
void Client::setMessage(std::string value, int size)
{
    if (size < 0)
        return;
    _message = value.substr(size, value.length() - size);
}

void Client::setParsingRequest(Prasing_Request &prsrqst)
{
    _parsing_reqst = prsrqst;
}
std::string &Client::getReuqst()
{
    return _reuqst;
}
void Client::setReuqst(char *value, int n)
{
    _reuqst.append(value, n);
}

int &Client::getEof()
{
    return _eof;
}

Configuration &Client::getConfiguration()
{
    return _config;
}




std ::vector<std ::string> ft_split(std::string str, std::string delimiter)
{
    std ::vector<std ::string> v;
    if (!str.empty())
    {
        size_t start = 0;
        do
        {
            size_t idx = str.find(delimiter, start);
            if (idx == std ::string::npos)
                break;
            int length = idx - start;
            v.push_back(str.substr(start, length));
            start += (length + delimiter.size());
        } while (true);
        v.push_back(str.substr(start));
    }
    return v;
}

int Client::find_Transfer_Encoding()
{
    if (_reuqst.find("Transfer-Encoding: ") == std::string::npos)
        return 0;
    int start = _reuqst.find("Transfer-Encoding: ") + strlen("Transfer-Encoding: ");
    size_t i = start;
    while (i < _reuqst.size() - 1)
    {
        if (_reuqst[i] == '\r' && _reuqst[i + 1] == '\n')
        {
            _Transfer_Encoding = _reuqst.substr(start, i - start);
            return 1;
        }
        i++;
    }
    return 0;
}

int Client::find_content_length()
{
    if (_reuqst.find("Content-Length: ") == std::string::npos)
        return 0;
    int start = _reuqst.find("Content-Length: ") + strlen("Content-Length: ");
    size_t i = start;
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

int Client::init_mayMap()
{
    std::string headr;
    std::cout<<"-----\n"<<_reuqst;
    if(_reuqst.find("\r\n\r\n")!= std::string::npos)
        return 1;
    headr = _reuqst.substr(0, _reuqst.find("\r\n\r\n"));
    headr = _reuqst.substr(_reuqst.find("\r\n") + 2, _reuqst.size());
    return 0;
}

int Client::find_request_eof()
{
    std::string farstline;
    // init_mayMap();
    if (find_content_length())
    {
        _readyToRecv = false;
        _cont_legth = atoi(_content_Length.c_str());
    }
    if (find_Transfer_Encoding())
    {
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
    if (!_Transfer_Encoding.compare("chunked") && (_reuqst.find("\r\n0\r\n") != std::string::npos))
        _eof = true;
    std ::vector<std ::string> res = ft_split(_reuqst, "\r\n");
    std ::string key;
    std ::string value;
    for (size_t i = 0; i < res.size(); i++)
    {
        key = "";
        value =  "";
        // if(res[i].find(":") != std::string::npos)
            key = res[i].substr(0, res[i].find(":"));
        // if(res[i].find(" ") + 1 != std::string::npos)
            value = res[i].substr(res[i].find(" ") + 1);
        _mymap.insert(std ::pair<std ::string, std::string>(key, value));
    }
    if (_mymap["Host"].find(":") != std::string::npos)
        _hostrqst = _mymap["Host"].substr(0, _mymap["Host"].find(":"));
    else
        _hostrqst = _mymap["Host"];
    return 0;
}
