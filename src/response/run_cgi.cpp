#include "Response.hpp"

int Response::run_cgi(std::string url, Configuration conf_serv)
{
    std ::string root = conf_serv.getroot() + url;
    std::cout << "root :" << root << std::endl;
    if (access(root.c_str(), F_OK) != -1)
        std::cout << "yes-------\n\n";
    return 1;
}
