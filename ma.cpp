#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

std::string read_request()
{
    std::string request;
    request = "GET / HTTP/1.1\r\n";
    request += "Host: localhost:8080\r\n";
    request += "Connection: keep-alive\r\n";
    request += "Cache-Control: max-age=0\r\n";
    request += "sec-ch-ua: 'Not_A Brand';v='99', 'Google Chrome';v='109', 'Chromium';v='109'\r\n";
    request += "sec-ch-ua-mobile: ?0\r\n";
    request += "sec-ch-ua-platform: 'Linux'\r\n";
    request += "Upgrade-Insecure-Requests: 1\r\n";
    request += "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/109.0.0.0 Safari/537.36\r\n";
    request += "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9\r\n";
    request += "Sec-Fetch-Site: none\r\n";
    request += "Sec-Fetch-Mode: navigate\r\n";
    request += "Sec-Fetch-User: ?1\r\n";
    request += "Sec-Fetch-Dest: document\r\n";
    request += "Accept-Encoding: gzip, deflate, br\r\n";
    request += "Accept-Language: en-US,en;q=0.9,fr-MA;q=0.8,fr;q=0.7,ar-MA;q=0.6,ar;q=0.5,en-CA;q=0.4,es-US;q=0.3,es;q=0.2\r\n";
    request += "Cookie: SL_G_WPT_TO=en; SL_GWPT_Show_Hide_tmp=undefined; SL_wptGlobTipTmp=undefined\r\n";
    request += "\r\n";
    return request;
}

int main()
{
    std::string request = read_request();
    // std::cout << request;
    if (request.find("\r\n\r\n") != std::string::npos)
        std::cout <<"yes" << std::endl;
}