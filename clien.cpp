#include "include/webserv.hpp"

int main(int argc, char **argv)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    connect(sock, (struct sockaddr *)&addr, sizeof(addr));
    char* hello = (char *)"wax asat hani";
    send(sock, hello, strlen(hello), 0);

}
