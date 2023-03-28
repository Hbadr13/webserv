

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
    std::string resp = "";
    resp += "GET / HTTP/1.1\r\n";
    resp += "Host: localhost:9030\r\n";
    resp += "Connection: keep-alive\r\n";
    resp += "Cache-Control: max-age=0\r\n";
    resp += "sec-ch-ua-mobile: ?0\r\n";
    resp += "sec-ch-ua-pl\r\n";
    resp += "1032\r\n";
    resp += "connected\r\n";
    resp += "GET /favicon.ico HTTP/1.1\r\n";
    resp += "Host: localhost:9030\r\n";
    resp += "Connection: keep-alive\r\n";
    resp += "sec-ch-ua-mobile: ?0\r\n";
    resp += "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/109.0.0.0 Safari/537.36\r\n";
    resp += "Accept: image/avif,image/webp,image/apng,image/svg+xml,image/*,*/*;q=0.8\r\n";
    resp += "Sec-Fetch-Site: same-origin\r\n";
    resp += "Sec-Fetch-Mode: no-cors\r\n";
    resp += "Sec-Fetch-Dest: image\r\n";
    resp += "Referer: http://localhost:9030/\r\n";
    resp += "Accept-Encoding: gzip, deflate, br\r\n";
    resp += "Accept-Language: en-US,en;q=0.9,fr-MA;q=0.8,fr;q=0.7,ar-MA;q=0.6,ar;q=0.5,en-CA;q=0.4,es-US;q=0.3,es;q=0.2\r\n";
    resp += "Cookie: SL_G_WPT_TO=en; SL_GWPT_Show_Hide_tmp=undefined; SL_wptGlobTipTmp=undefined\r\n";
    resp += "Content-Length: 16693\r\n";
    resp += "\r\n";
    // std::string s1 = resp.substr(resp.find("Content-Length") + strlen("Content-Length: "),s1.size());
    std::string s1 = resp.substr(1,2);
    std::cout<<s1<<std::endl;
    std::string contlent = resp.substr(resp.find("Content-Length") + strlen("Content-Length: "),10);
    std::cout<<contlent<<std::endl;

}
