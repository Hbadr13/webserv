#include "src/Configfile/Configuration.hpp"
#include "src/Webserv.hpp"

char *getPath(int ac, char **av)
{

    std::string path;
    if (ac == 1)
        return (char*)"config/defualt.conf";
    else if (ac > 2)
        return NULL;
    if (av[1])
    {
        DIR *dir = opendir(av[1]);
        if (dir)
        {
            closedir(dir); 
            return NULL;
        }
    }
    path = av[1];
    if (path.size() < 6)
        return NULL;
    if (path.substr(path.size() - 5, path.size()) != ".conf")
        return NULL;
    return av[1];
}

int main(int argc, char **argv)
{
    char *path;
    path = getPath(argc, argv);
    if(path == NULL)
        return  std::cout<<"Syntax Error\n", 1;
    Webserv myserver(path);
    if (-1 == myserver.init_server())
        return 1;
    myserver.run_server();
    return 0;
}
