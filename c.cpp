

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <vector>
#include <fcntl.h>
#include <map>
#include <sys/time.h>

int main()
{
    std::vector<int> _pollfd;
    _pollfd.push_back(21);
    _pollfd.push_back(22);
    _pollfd.push_back(23);
    _pollfd.push_back(24);
    _pollfd.push_back(25);
    for (int i = 0; i < _pollfd.size(); i++)
        std::cout << _pollfd[i] << " ";
    std::cout << "\n------------\n";
    _pollfd.erase(_pollfd.begin() + 2);
    for (int i = 0; i < _pollfd.size(); i++)
        std::cout << _pollfd[i] << " ";
}
