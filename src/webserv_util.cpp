#include "../include/webserv.hpp"

int msg_error(int status)
{

    write(2, "error ", 6);
    std::cout << status << std::endl;
    return -1;
}