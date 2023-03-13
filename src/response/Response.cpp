#include "Response.hpp"
#include <ctime>
#include <fstream>
#include <filesystem>
#include <dirent.h>

#include <iostream>
Response::Response()
{
}
std::string int_to_string(int numb)
{
    std::ostringstream ss;
    ss << numb;
    return ss.str();
}

std ::string chec_url(std ::string urll)
{
    int i = 0;
    int j = 0;
    std ::string result;
    while (urll[i] == '/')
        i++;
    while (urll[i] != '/' && i < strlen(urll.c_str()))
    {
        if (j == 0)
        {
            result = "/";
            j = 1;
        }
        result += urll[i];
        i++;
    }
    return result;
}

std::pair<Location, std::string> find_location(std::string url, Configuration conf_serv)
{
    url = parsing_url(url);
    std::vector<std::string> vect_str = split_string(url, '/');
    std::string url_check;
    int len = vect_str.size();
    while (1)
    {
        url_check = "/";
        int i = 0;
        while (i < len)
        {
            url_check += vect_str[i];
            if (i != len - 1)
                url_check += "/";
            i++;
        }
        len--;
        std::map<std::string, std::map<std::string, std::vector<std::string> > >::iterator it = conf_serv.getlocations().begin();
        while (it != conf_serv.getlocations().end())
        {
            if (!it->first.compare(url_check))
            {
                // Location l()
                Location location(conf_serv, it->first);
                // std::cout << it->first << std::endl;
                return std::pair<Location,std::string>(location, it->first);
            }
            it++;
        }
        if (!url_check.compare("/"))
            break;
    }
    return std::pair<Location,std::string>(Location(), std::string());
}

Response::Response(Prasing_Request rq, Configuration conf_serv)
{

    // status = rq.get_status();
    // mymap = rq.get_mymap();
    // std ::string url = rq.get_url();
    // std ::string def_url = chec_url(url);
    // Location loct(conf_serv, "/");
    // std ::string method = rq.get_method();
    // std ::string autoindex = "on";
    // // if(autoindex == "off")
    // //    url1 = "/index.html";
    // std ::string root = "../my_web/" + url;
    std::pair<Location, std::string> location_and_url = find_location(rq.get_url(), conf_serv);
    // std::cout<<location_and_url.first.getindex() << std::endl;
    run_cgi(location_and_url.first, location_and_url.second , conf_serv);
    // if (1)
    // {

    //     std::string url1;
    //     if (url == "/return")
    //     {
    //         std ::string bady;
    //         bady = "HTTP/1.1 301 Moved Permanently";
    //         bady.append("\nLocation: ");
    //         bady.append("../my_web/www");
    //         bady.append("\n");
    //         respons = bady;
    //         return;
    //     }
    //     if (autoindex == "on")
    //     {

    //         DIR *dir;
    //         dirent *ent;
    //         std ::string bady;
    //         std ::string msg;
    //         bady.append("HTTP/1.1 ");
    //         bady.append(int_to_string(status));
    //         bady.append(" OK \nServer: Server \nDate: ");
    //         time_t now = time(0);
    //         char *time = ctime(&now);
    //         bady.append(time);
    //         bady.append("Content-Type: text/html\nContent-Length: ");

    //         if ((dir = opendir(root.c_str())) != NULL)
    //         {
    //             msg = "<!DOCTYPE html>\n\
    //                     <html lang=\"en\">\n\
    //                     <ol> ";
    //             while ((ent = readdir(dir)) != NULL)
    //             {
    //                 std ::string name = ent->d_name;
    //                 std::string name1;
    //                 if (url[0] == '/' && !url[1])
    //                     name1 = name;
    //                 else
    //                     name1 = url + "/" + name;
    //                 msg += "\n<li><a href=\"" + name1 + "\">" + name + "</a></li>\n";
    //             }
    //             msg += "</ol>\n\
    //                        </html>";
    //             int len = msg.length();
    //             bady.append(int_to_string(len));
    //             bady.append("\n\n");
    //             bady.append(msg);
    //             respons = bady;
    //             closedir(dir);
    //             return;
    //         }
    //         else if (int i = open(root.c_str(), O_RDWR))
    //         {
    //             std::ifstream file(root.c_str());
    //             std::string http;
    //             if (file)
    //             {
    //                 std::ostringstream str;
    //                 str << file.rdbuf();
    //                 http = str.str();
    //             }
    //             int len = http.length();
    //             bady.append(int_to_string(len));
    //             bady.append("\n\n");
    //             bady.append(http);
    //             respons = bady;
    //             close(i);
    //             return;
    //         }
    //     }
    //     else
    //     {
    //         std ::string url2 = root + url1;
    //         int i = open(url2.c_str(), O_RDWR);
    //         std ::string bady;
    //         std::ifstream file(url2.c_str());
    //         std::string http;
    //         if (file)
    //         {
    //             std::ostringstream str;
    //             str << file.rdbuf();
    //             http = str.str();
    //         }
    //         bady.append("HTTP/1.1 ");
    //         bady.append(int_to_string(status));
    //         bady.append(" OK \nServer: Server\nDate: ");
    //         time_t now = time(0);
    //         char *time = ctime(&now);
    //         bady.append(time);
    //         bady.append("Content-Type: text/html\nContent-Length: ");
    //         int len = http.length();
    //         bady.append(int_to_string(len));
    //         bady.append("\n\n");
    //         bady.append(http);
    //         respons = bady;

    //         close(i);
    //         return;
    //     }
    // }
}

std ::string Response::get_respons()
{
    return (this->respons);
}