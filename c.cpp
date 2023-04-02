#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
using namespace std;
#include <unistd.h>
string httpResponse;
int bytesRecv;
void sethttpre(char *buf)
{
    std::cout << httpResponse << std::endl;
    httpResponse.append(buf, bytesRecv);
}
int main()
{
    char buf[1024];
    int clientSocket = open("file", O_RDONLY);
    std::cout << clientSocket << std::endl;
    while ((bytesRecv = read(clientSocket, buf, 1024)) > 0)
    {
        write(2, "hna\n", 4);
        sethttpre(buf);
        // httpResponse.append(buf, sizeof(buf));
    }
    std::cout << httpResponse;
    // extract image data from response
    // size_t pos = httpResponse.find("\r\n\r\n");
    // if (pos != string::npos)
    // {
    //     pos += 4; // skip end of headers
    //     size_t contentLengthPos = httpResponse.find("Content-Length: ");
    //     if (contentLengthPos != string::npos)
    //     {
    //         contentLengthPos += 16;
    //         size_t contentLengthEndPos = httpResponse.find("\r\n", contentLengthPos);
    //         if (contentLengthEndPos != string::npos)
    //         {
    //             int contentLength = stoi(httpResponse.substr(contentLengthPos, contentLengthEndPos - contentLengthPos));
    //             string imageData = httpResponse.substr(pos, contentLength);
    //             cout << "Image data size: " << imageData.size() << endl;
    //         }
    //     }
    // }
    return 0;
}
