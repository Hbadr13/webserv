#include "src/Configfile/Configuration.hpp"
#include "src/Webserv.hpp"


int main(int argc, char **argv)
{
    char *path;
    if (argc == 1)
        path = (char *)"config/defualt.conf";
    else if(argc > 2)
        return 1;
    else
        path = argv[1];
    Webserv myserver(path);
    if (-1 == myserver.init_server())
        return 1;
    myserver.run_server();
    return 0;
}
