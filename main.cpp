#include "src/webserv.hpp"

#include "src/Configfile/Configuration.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
        exit(1);
    Webserv myserver(argv[1]);
    if (-1 == myserver.init_server())
        return 1;
    // while(1);
    myserver.run_server();
    return 0;
}
