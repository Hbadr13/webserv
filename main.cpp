#include "include/webserv.hpp"
int main(int argc, char **argv)
{
    // std::cout<<sizeof(socklen_t);

    Webserv myserver(2022, 2);
    if (-1 == myserver.init_server())
        return 1;
    myserver.run_server();

    return 0

}
