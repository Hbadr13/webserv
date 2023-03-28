

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

std::string find_content_length(std::string resp)
{
    if (resp.find("Content-Length") == std::string::npos)
        return "";
    int start = resp.find("Content-Length") + strlen("Content-Length: ");
    int i = start;
    while (i < resp.size() - 1)
    {
        if (resp[i] == '\r' && resp[i + 1] == '\n')
            return resp.substr(start, i - start);
        i++;
    }
    return "";
}

int main()
{
    std::string resp = "";
    resp = "GET / HTTP/1.1111";

    std::cout << resp.substr(15, resp.length()-15)<<std::endl;
}
