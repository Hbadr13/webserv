#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <fcntl.h>
#include <iostream>
#define content_length 100
#define MAX_CLIENTS 1000

std::string return_body()
{
    std::string body = "";
    body += "POST /c HTTP/1.1\r\n";
    body += "Transfer-Encoding: chunked\r\n";
    body += "User-Agent: PostmanRuntime/7.31.0\r\n";
    body += "Accept: */*\r\n";
    body += "Postman-Token: 98495951-c25c-4377-b6db-462679e2dca5\r\n";
    body += "Host: localhost:9092\r\n";
    body += "Accept-Encoding: gzip, deflate, br\r\n";
    body += "Content-Type: multipart/form-data; boundary=--------------------------882808754294179912880155\r\n";
    body += "Content-Length: 484\r\n";
    body += "\r\n";
    body += "8e\r\n";
    body += "----------------------------882808754294179912880155\r\n";
    body += "Content-Disposition: form-data; name=''; filename='file.cpp'\r\n";
    body += "Content-Type: text/x-c\r\n";
    body += "\r\n";
    body += "\r\n";
    body += "11c\r\n";
    body += "#include <stdio.h>\n";
    body += "#include <stdlib.h>\n";
    body += "#include <string.h>\n";
    body += "#include <errno.h>\n";
    body += "#include <unistd.h>\n";
    body += "#include <sys/socket.h>\n";
    body += "\n";
    body += "\n";
    body += "\n";
    body += "\n";
    body += "\n";
    body += "\n";
    body += "#include <netinet/in.h>\n";
    body += "#include <arpa/inet.h>\n";
    body += "#include <poll.h>\n";
    body += "#include <fcntl.h>\n";
    body += "#include <iostream>\n";
    body += "#define content_length 100\n";
    body += "#define MAX_CLIENTS 1000\n";
    body += "\r\n";
    body += "3a\r\n";
    body += "\r\n";
    body += "----------------------------882808754294179912880155--\r\n";
    body += "\r\n";
    body += "0\r\n";
    body += "\r\n";
    return body;
}

std ::string ft_chanked(std ::string body)
{
    int i = 0;
    int tr = 0;
    std ::string chunked;
        std ::string hex;
    while (i < body.length())
    {
        if (body[i] == '\r' && body[i + 1] == '\n')
            i += 2;
        while (body[i] != '\r' && body[i + 1] != '\n')
        {
            hex += body[i];
            i++;
        }
        // std :: cout << "\n||||||||||||" << hex << "|||||||||||\n";
        tr = (int)strtol(hex.c_str(), NULL, 16);
        i += 2;
        while (tr > 0)
        {
            chunked += body[i];
            tr--;
            i++;
        }
    }
    std :: cout << hex.size() << std :: endl;
    return chunked;
}

int main()
{
    std::string str = ft_chanked(return_body());
    // std::cout << return_body().size() << std::endl;
    // std::cout << str;
    // std::cout << str.size() << std::endl;
}

