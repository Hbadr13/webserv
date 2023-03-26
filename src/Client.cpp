#include "Client.hpp"

Client::Client()
{
}
Client::~Client()
{

}
Client::Client(Configuration &confi)
{
    _config = confi;
}
std::string Client::getReuqst()
{
    return _reuqst;
}
void Client::setReuqst(std::string value)
{
    _reuqst = value;
}

