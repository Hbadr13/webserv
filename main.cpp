#include "include/webserv.hpp"

int main(int argc, char **argv)
{
    Webserv myserver(2012, 5);
    if (-1 == myserver.init_server())
        return 1;
    myserver.run_server();

    std::string host = "localhost";
    std::string port = "80";
    return 0;

}

